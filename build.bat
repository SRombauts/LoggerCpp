@REM Copyright (c) 2013 Sébastien Rombauts (sebastien.rombauts@gmail.com)
@REM
@REM Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
@REM or copy at http://opensource.org/licenses/MIT)
mkdir build
cd build
cmake .. -G "Visual Studio 10"
cmake --build .
@REM ctest .
cd ..