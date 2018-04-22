#!/usr/bin/env bash

set -e

git add .

git commit -m "$1"

git push origin master