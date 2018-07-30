//$Header: svn://localhost/dtapublic/projs/ets/trunk/build/ets_dedup/win/ets_dedup.cpp 233 2018-07-29 16:54:04Z dashley $
//{1e390e64-2351-40bd-b611-3c2d0d16b2f0}
//-------------------------------------------------------------------------------------------------
//Copyright (c) 2018, David T. Ashley
//
//This file is part of "ets_dedup", a program for eliminating duplicate files in a subdirectory
//tree.
//
//This source code and any program in which it is compiled/used is licensed under the MIT License,
//reproduced below.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files(the "Software"), to deal in the
//Software without restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the
//Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-------------------------------------------------------------------------------------------------
extern "C" int c_main(int argc, char **argv);

int main(int argc, char **argv)
{
   int rv;

   //Call the C program from C++.
   rv = c_main(argc, argv);

   return(rv);
}
