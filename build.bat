@REM Copyright (c) 2013-2018 Sébastien Rombauts (sebastien.rombauts@gmail.com)
@REM
@REM Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
@REM or copy at http://opensource.org/licenses/MIT)
mkdir build
cd build
cmake ..
cmake --build .
@REM ctest .
cd ..