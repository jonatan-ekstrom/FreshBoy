#!/bin/bash

set -e # Exit on all errors.

printf 'Welcome to the FreshBoy installation script...\n\n'

read -p 'Build directory (~/build): ' _build

read -p 'Install directory (~/install): ' _install

read -p 'Build in release mode (Y): ' _release

if ! [[ "$_release" =~ [Nn] ]]; then
    read -p 'Enable link time optimization: (Y): ' _lto
fi

read -p 'Remove build directory after installing (Y): ' _clean

build="${_build:-~/build}"
build="${build/#\~/$HOME}"

if [[ -d "$build" ]]; then
    echo 'Build directory already exists, exiting...'
    exit 1
fi

install="${_install:-~/install}"
install="${install/#\~/$HOME}"

if [[ -d "$install" ]]; then
    echo 'Install directory already exists, exiting...'
    exit 1
fi

if ! [[ "$_release" =~ [Nn] ]]; then
    config='Release'
else
    config='Debug'
fi

lto_status='Disabled'
lto_state='OFF'
if ! [[ "$_lto" =~ [Nn] ]]; then
    lto_status='Enabled'
    lto_state='ON'
fi

if ! [[ "$_clean" =~ [Nn] ]]; then
    clean='Yes'
else
    clean='No'
fi

printf '\nYou have entered the following configuration...\n'
echo '-------------------------------------------------'
echo 'Build directory: '"$build"
echo 'Install directory: '"$install"
echo 'Configuration: '"$config"
if [[ "$config" = 'Release' ]]; then
    echo 'Link time optimization: '"$lto_status"
fi
echo 'Remove build directory: '"$clean"
echo '-------------------------------------------------'
printf '\n'

read -p 'Is this correct? (Y): ' correct

if [[ "$correct" =~ [Nn] ]]; then
    echo 'Exiting...'
    exit 1
fi

source="$PWD"

logFile="$build"/build.log

printf '\nStarting build...\n'

echo '1: Creating directories...'
mkdir "$build"
mkdir "$install"

echo '2: Running cmake...'
cmake -G Ninja -S "$source" -B "$build" -DCMAKE_BUILD_TYPE="$config" -DCMAKE_INSTALL_PREFIX="$install" -DUSE_LTO="$lto_state" >> "$logFile"

echo '3: Compiling...'
cmake --build "$build" >> "$logFile"

echo '4: Installing...'
cmake --install "$build" >> "$logFile"

if [[ "$clean" = 'Yes' ]]; then
    echo '5: Cleaning up...'
    rm -rf "$build"
fi

echo 'Done!'
