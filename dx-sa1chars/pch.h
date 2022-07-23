// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

// modloader lib
#include <SADXModLoader.h>
#include <ModelInfo.h>

// mod
#include "amy/amy_decl.h"
#include "amy/amy_func.h"
#include "big/big_decl.h"
#include "big/big_func.h"
#include "e102/gam_decl.h"
#include "e102/gam_func.h"
#include "eggman/egg_decl.h"
#include "eggman/egg_func.h"
#include "knuckles/knu_decl.h"
#include "knuckles/knu_func.h"
#include "miles/mil_decl.h"
#include "miles/mil_func.h"
#include "sonic/son_decl.h"
#include "sonic/son_func.h"
#include "tikal/tik_decl.h"
#include "tikal/tik_func.h"

#endif //PCH_H
