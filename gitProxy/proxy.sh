#!/bin/sh
export proxyDir="`dirname \"$0\"`"
export defaultGit="`which git`"
export PATH="$proxyDir:$PATH"
bash
