from __future__ import annotations

from datetime import datetime
from pathlib import Path
from typing import Iterable

from reportlab.lib import colors
from reportlab.lib.pagesizes import A4, landscape
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen.canvas import Canvas


ROOT = Path(__file__).resolve().parent
OUTPUT_DIR = ROOT / "output" / "pdf"
PDF_PATH = OUTPUT_DIR / "acm_template_print.pdf"
INDEX_PATH = OUTPUT_DIR / "acm_template_index.md"

PAGE_WIDTH, PAGE_HEIGHT = landscape(A4)
MARGIN_X = 32
TOP_Y = PAGE_HEIGHT - 34
BOTTOM_Y = 30
CODE_FONT_SIZE = 6.4
CODE_LEADING = 8.0
TITLE_FONT_SIZE = 8.6
COLUMN_GAP = 18
COLUMN_WIDTH = (PAGE_WIDTH - 2 * MARGIN_X - COLUMN_GAP) / 2

FONT_DIR = Path(r"C:\Windows\Fonts")
CODE_FONT = "Consolas"
CJK_FONT = "MicrosoftYaHei"

SECTIONS = [
    ("基础", ["BasicAlgo.cpp", "BinarySearch.cpp", "Sortings.cpp", "BigInteger.cpp"]),
    ("数据结构", None),
    ("动态规划", None),
    ("图论", None),
    ("数学", None),
    ("字符串", None),
]


def register_fonts() -> None:
    """Register a monospace font and a Chinese-capable fallback font."""
    pdfmetrics.registerFont(TTFont(CODE_FONT, str(FONT_DIR / "consola.ttf")))
    pdfmetrics.registerFont(TTFont(CJK_FONT, str(FONT_DIR / "msyh.ttc")))


def read_text(path: Path) -> str:
    """Read UTF-8 and UTF-16 source files without changing their contents."""
    data = path.read_bytes()
    if data.startswith((b"\xff\xfe", b"\xfe\xff")):
        return data.decode("utf-16")
    if data.startswith(b"\xef\xbb\xbf"):
        return data.decode("utf-8-sig")
    return data.decode("utf-8")


def source_files() -> list[tuple[str, Path]]:
    """Return printable board files in a stable section and filename order."""
    result: list[tuple[str, Path]] = []
    for section, explicit in SECTIONS:
        if explicit is not None:
            paths = [ROOT / name for name in explicit if (ROOT / name).exists()]
        else:
            directory = {
                "数据结构": "DataStructure",
                "动态规划": "DynamicProgramming",
                "图论": "Graph",
                "数学": "Math",
                "字符串": "String",
            }[section]
            paths = sorted((ROOT / directory).glob("*.cpp"), key=lambda p: p.name.lower())
        for path in paths:
            if path.name in {"PRINT_BUNDLE.cpp", "temp.cpp"}:
                continue
            result.append((section, path))
    return result


def display_name(path: Path) -> str:
    return path.relative_to(ROOT).as_posix()


def line_font(line: str) -> str:
    return CJK_FONT if any(ord(ch) > 127 for ch in line) else CODE_FONT


def split_for_width(line: str, font: str, size: float, max_width: float) -> list[str]:
    """Wrap only when necessary so long code lines do not run off the page."""
    if not line:
        return [""]
    result: list[str] = []
    rest = line.expandtabs(4)
    while rest:
        if pdfmetrics.stringWidth(rest, font, size) <= max_width:
            result.append(rest)
            break
        lo, hi = 1, len(rest)
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if pdfmetrics.stringWidth(rest[:mid], font, size) <= max_width:
                lo = mid
            else:
                hi = mid - 1
        cut = max(1, lo)
        result.append(rest[:cut])
        rest = rest[cut:]
    return result


def draw_header(canvas: Canvas, text: str, page_no: int | None = None) -> None:
    canvas.setFillColor(colors.HexColor("#233047"))
    canvas.setFont(CJK_FONT, 9)
    canvas.drawString(MARGIN_X, PAGE_HEIGHT - 22, text)
    if page_no is not None:
        canvas.setFillColor(colors.HexColor("#667085"))
        canvas.setFont(CODE_FONT, 8)
        canvas.drawRightString(PAGE_WIDTH - MARGIN_X, PAGE_HEIGHT - 22, f"{page_no}")
    canvas.setStrokeColor(colors.HexColor("#D0D5DD"))
    canvas.line(MARGIN_X, PAGE_HEIGHT - 27, PAGE_WIDTH - MARGIN_X, PAGE_HEIGHT - 27)


def draw_footer(canvas: Canvas) -> None:
    canvas.setStrokeColor(colors.HexColor("#D0D5DD"))
    canvas.line(MARGIN_X, 22, PAGE_WIDTH - MARGIN_X, 22)
    canvas.setFillColor(colors.HexColor("#667085"))
    canvas.setFont(CJK_FONT, 7.5)
    canvas.drawString(MARGIN_X, 11, "ACM Competition Template - printable board library")


def draw_cover(canvas: Canvas, files: list[tuple[str, Path]]) -> None:
    canvas.setFillColor(colors.HexColor("#172033"))
    canvas.rect(0, 0, PAGE_WIDTH, PAGE_HEIGHT, stroke=0, fill=1)
    canvas.setFillColor(colors.HexColor("#7DD3FC"))
    canvas.setFont(CODE_FONT, 15)
    canvas.drawString(MARGIN_X + 18, PAGE_HEIGHT - 105, "ACM_COMPETITION_TEMPLATE")
    canvas.setFillColor(colors.white)
    canvas.setFont(CJK_FONT, 28)
    canvas.drawString(MARGIN_X + 18, PAGE_HEIGHT - 160, "算法竞赛板子")
    canvas.setFillColor(colors.HexColor("#CBD5E1"))
    canvas.setFont(CJK_FONT, 12)
    canvas.drawString(MARGIN_X + 20, PAGE_HEIGHT - 190, "按模块打印，按需复制")
    canvas.setFont(CJK_FONT, 10)
    canvas.drawString(MARGIN_X + 20, PAGE_HEIGHT - 240, f"板子数量：{len(files)}")
    canvas.drawString(MARGIN_X + 20, PAGE_HEIGHT - 260, f"生成时间：{datetime.now():%Y-%m-%d %H:%M}")
    canvas.setFillColor(colors.HexColor("#7DD3FC"))
    canvas.setFont(CJK_FONT, 9)
    canvas.drawString(MARGIN_X + 20, 48, "说明：PDF 直接从当前 .cpp 板子生成，Markdown 仅作为目录索引。")
    canvas.showPage()


def draw_index(canvas: Canvas, files: list[tuple[str, Path]]) -> None:
    draw_header(canvas, "目录", 2)
    canvas.setFillColor(colors.HexColor("#172033"))
    canvas.setFont(CJK_FONT, 18)
    canvas.drawString(MARGIN_X, TOP_Y - 22, "板子目录")

    groups: dict[str, list[Path]] = {}
    for section, path in files:
        groups.setdefault(section, []).append(path)
    sections = list(groups.items())
    split = (len(sections) + 1) // 2

    def draw_column(items: list[tuple[str, list[Path]]], x: float) -> None:
        y = TOP_Y - 55
        for section, paths in items:
            canvas.setFillColor(colors.HexColor("#2563EB"))
            canvas.setFont(CJK_FONT, 10.5)
            canvas.drawString(x, y, section)
            y -= 16
            canvas.setFillColor(colors.HexColor("#344054"))
            canvas.setFont(CODE_FONT, 8.2)
            for path in paths:
                canvas.drawString(x + 14, y, display_name(path))
                y -= 13
            y -= 6

    draw_column(sections[:split], MARGIN_X)
    draw_column(sections[split:], PAGE_WIDTH / 2 + 8)
    draw_footer(canvas)
    canvas.showPage()


def draw_code_files(canvas: Canvas, files: list[tuple[str, Path]], page_no: int) -> None:
    """Flow all source files through two columns from left to right."""
    column = 0
    y = TOP_Y - 20
    column_x = [MARGIN_X, PAGE_WIDTH / 2 + COLUMN_GAP / 2]
    page_title = "算法竞赛板子 / 双栏代码"

    def next_column() -> None:
        nonlocal column, y, page_no
        if column == 0:
            column = 1
            y = TOP_Y - 20
        else:
            draw_footer(canvas)
            canvas.showPage()
            page_no += 1
            draw_header(canvas, page_title, page_no)
            column = 0
            y = TOP_Y - 20

    draw_header(canvas, page_title, page_no)
    for section, path in files:
        title = f"{section} / {display_name(path)}"
        if y < BOTTOM_Y + 28:
            next_column()
        x = column_x[column]
        canvas.setFillColor(colors.HexColor("#172033"))
        canvas.setFont(CJK_FONT, TITLE_FONT_SIZE)
        canvas.drawString(x, y, display_name(path))
        y -= 14

        for line_no, raw_line in enumerate(read_text(path).splitlines(), 1):
            font = line_font(raw_line)
            chunks = split_for_width(raw_line, font, CODE_FONT_SIZE, COLUMN_WIDTH - 38)
            for chunk_no, chunk in enumerate(chunks):
                if y < BOTTOM_Y + CODE_LEADING:
                    next_column()
                    x = column_x[column]
                if chunk_no == 0:
                    canvas.setFillColor(colors.HexColor("#98A2B3"))
                    canvas.setFont(CODE_FONT, CODE_FONT_SIZE)
                    canvas.drawRightString(x + 27, y, str(line_no))
                canvas.setFillColor(colors.HexColor("#1D2939"))
                canvas.setFont(font, CODE_FONT_SIZE)
                canvas.drawString(x + 34, y, chunk)
                y -= CODE_LEADING

        if y > BOTTOM_Y + 10:
            canvas.setStrokeColor(colors.HexColor("#E4E7EC"))
            canvas.line(x + 34, y + 2, x + COLUMN_WIDTH, y + 2)
            y -= 7

    draw_footer(canvas)
    canvas.showPage()


def write_index(files: Iterable[tuple[str, Path]]) -> None:
    lines = [
        "# ACM Competition Template 板子目录",
        "",
        "> PDF 由 `build_template_pdf.py` 直接从当前 C++ 板子生成。",
        "",
    ]
    current = ""
    for section, path in files:
        if section != current:
            current = section
            lines.extend([f"## {section}", ""])
        lines.append(f"- `{display_name(path)}`")
    INDEX_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    register_fonts()
    files = source_files()
    write_index(files)
    canvas = Canvas(str(PDF_PATH), pagesize=landscape(A4), pageCompression=1)
    canvas.setTitle("ACM Competition Template")
    canvas.setAuthor("MengPaul")
    draw_cover(canvas, files)
    draw_index(canvas, files)
    draw_code_files(canvas, files, 3)
    canvas.save()
    print(f"Wrote {PDF_PATH}")
    print(f"Wrote {INDEX_PATH}")
    print(f"Files: {len(files)}")


if __name__ == "__main__":
    main()
