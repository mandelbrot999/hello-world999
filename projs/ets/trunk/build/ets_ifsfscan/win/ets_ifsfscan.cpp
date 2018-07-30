//$Header: svn://localhost/dtapublic/projs/ets/trunk/build/ets_ifsfscan/win/ets_ifsfscan.cpp 225 2018-07-22 22:53:16Z dashley $
//{1ea3115f-1f6d-4f0b-979b-ad92423db59a}
//-------------------------------------------------------------------------------------------------
//Copyright (c) 2018, David T. Ashley
//
//This file is part of "ets_ifsfscan", a program for identifying gross formatting anomalies in
//source files.
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
