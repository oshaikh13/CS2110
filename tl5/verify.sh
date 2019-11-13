#!/bin/bash
e=0; [[ $(sha512sum tl5.h | cut -d " " -f 1) == 197531cd537612270288c03ebb2fdbaaba08486b9db69f494b43270789d8cf8ce2a0f47634b52f16a8b0253e9b28950a917e31b55e8846d973f364a4e905ccd8 ]] || { printf 'error: tl5.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
