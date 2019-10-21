#!/bin/bash
e=0; [[ $(sha512sum errcodes.h | cut -d " " -f 1) == "a729c7a3d58e1e0bddac14d46b390258a52454d4960c80323c41d85cd5831add95a2dc71e60b573e2a89c2acab32241b6c06a0c2fba3f182e5e8d0cf8b92c968" ]] || { printf '*****ERROR: errcodes.h was modified! Undo your changes or re-download the homework!*****\n'>&2; e=1; }; exit $e
