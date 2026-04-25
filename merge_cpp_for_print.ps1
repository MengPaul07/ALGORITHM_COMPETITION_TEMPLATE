param(
	[string]$Root = ".",
	[string]$OutFile = "PRINT_BUNDLE.cpp",
	[string[]]$Exclude = @("PRINT_BUNDLE.cpp", "temp.cpp", "aaa.cpp")
)

$ErrorActionPreference = "Stop"

function Resolve-NormalizedPath {
	param([string]$Path)
	return (Resolve-Path $Path).Path
}

$rootPath = Resolve-NormalizedPath -Path $Root
$outputPath = Join-Path $rootPath $OutFile

$allCpp = Get-ChildItem -Path $rootPath -Filter "*.cpp" -File |
	Sort-Object Name

$filteredCpp = $allCpp | Where-Object {
	$name = $_.Name
	-not ($Exclude -contains $name)
}

if (-not $filteredCpp -or $filteredCpp.Count -eq 0) {
	throw "No .cpp files found after filtering in: $rootPath"
}

$line = "// " + ("=" * 78)

$header = @(
	"// Auto-generated print bundle",
	"// Source root: $rootPath",
	"// Generated at: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')",
	"// Files count: $($filteredCpp.Count)",
	$line,
	""
)

Set-Content -Path $outputPath -Value $header -Encoding UTF8

foreach ($file in $filteredCpp) {
	$title = @(
		$line,
		"// FILE: $($file.Name)",
		$line,
		""
	)

	Add-Content -Path $outputPath -Value $title -Encoding UTF8

	$content = Get-Content -Path $file.FullName -Encoding UTF8
	Add-Content -Path $outputPath -Value $content -Encoding UTF8
	Add-Content -Path $outputPath -Value "" -Encoding UTF8
}

Write-Host "Merged $($filteredCpp.Count) files to: $outputPath"
Write-Host "Excluded: $($Exclude -join ', ')"
