/*
 * =====================================================================================
 *
 *       Filename:  main.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 27 July 2015 11:54:06  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */

void RunAiwuTextFile()
{
    gROOT->ProcessLine(".L AiwuTextFile.C");
    gROOT->ProcessLine("AiwuTextFile t");
    gROOT->ProcessLine("t.Loop()");
}
