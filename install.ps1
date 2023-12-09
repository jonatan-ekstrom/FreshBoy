Write-Host "Welcome to the FreshBoy installation script..." -ForegroundColor Cyan
Write-Host ""

$env:ErrorActionPreference = "Stop"

function Read-Default($prompt, $default){
    $response = Read-Host -Prompt "$prompt ($default)"
    if ([string]::IsNullOrEmpty($response)) {$default} else {$response}
}

$build = Read-Default 'Build directory:' $env:USERPROFILE\build
$install = Read-Default 'Install directory:' $env:USERPROFILE\install
$release = Read-Default 'Build in release config:' 'Y'
$clean = Read-Default 'Remove build directory after installing:' 'Y'

if (Test-Path $build) {
    Write-Host "Build directory already exists, exiting..." -ForegroundColor Red
    exit 1
}

if (Test-Path $install) {
    Write-Host "Install directory already exists, exiting..." -ForegroundColor Red
    exit 1
}

if (![regex]::IsMatch($release, "[Nn]")) {
    $config = "Release"
} else {
    $config = "Debug"
}

$clean = !([regex]::IsMatch($clean, "[Nn]"))
$remove = if ($clean) { "Yes" } else { "No" }

Write-Host ""
Write-Host "You have entered the following configuration..." -ForegroundColor Green
Write-Host "-------------------------------------------------"
Write-Host "Build directory: $build"
Write-Host "Install directory: $install"
Write-Host "Configuration: $config"
Write-Host "Remove build directory: $remove"
Write-Host "-------------------------------------------------"
Write-Host ""

$correct = Read-Host -Prompt "Is this correct? (Y)"
if ([regex]::IsMatch($correct, "[Nn]")) {
    Write-Host "Exiting..." -ForegroundColor Red
    exit 1
}

$source = (Get-Location).Path
$log = Join-Path $build "build.log"

Write-Host ""
Write-Host "Starting build..." -ForegroundColor Green

Write-Host "1: Creating directories..."
New-Item -ItemType Directory -Path $build -Force | Out-Null
New-Item -ItemType Directory -Path $install -Force | Out-Null

Write-Host "2: Running cmake..."
cmake -G Ninja -S $source -B $build -DCMAKE_BUILD_TYPE="$config" -DCMAKE_INSTALL_PREFIX="$install" | Add-Content $log

Write-Host "3: Compiling..."
cmake --build $build | Add-Content $log

Write-Host "4: Installing..."
cmake --install $build | Add-Content $log

if ($clean) {
    Write-Host "5: Cleaning up..."
    Remove-Item -Recurse -Force $build
}

Write-Host "Done!" -ForegroundColor Green
