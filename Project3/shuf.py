#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
import argparse, string
from optparse import OptionParser

class randline:
    def __init__(self, filename, rnge, userinput, lo, hi):
        self.lines = []
        if rnge != "\n":
            inp = ""
            while lo <= hi:
                inp += str(lo)
                inp += "\n"
                lo += 1
                self.lines.append(inp)
                inp = ""
            
        elif userinput == True:
            self.lines = filename
            
        else:    
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

        for i in range(len(self.lines)):
            self.lines[i] = (self.lines[i])[:-1]

    def chooseline(self):
        return random.choice(self.lines)

    def printvals(self, rep, linecount, numlines):
        if rep == True:
            cnt = 0
            while cnt < numlines:
                print(self.chooseline())
                if linecount == True:
                    cnt += 1
        else:
            while self.lines:
                choice = self.chooseline()
                print(choice)
                self.lines.remove(choice)
        

    

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE
  or:  %prog -i LO-HI [OPTION]...

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="numlines", default="\n",
                      help="Max line output (Default all)")
    parser.add_option("-i", "--input-range",
                      action="store", dest="range",default="\n",
                      help="Shuffles numeric input range")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="rep", default=False,
                      help="Repeats shuffling")
    
    options, args = parser.parse_args(sys.argv[1:])
    
    range = options.range
    rep = options.rep
    
    if options.numlines == "\n":
        linecount = False
        numlines = 1
    else:
        try:
            numlines = int(options.numlines)
        except:
            parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
        linecount = True
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) != 1 and len(args) != 0:
        parser.error("wrong number of operands")

    userinput=False
    i1 = -1
    i2 = -1
    
    if len(args) != 0 and args[0] != "-":
        input_file = args[0]
    elif len(args) == 0 or args[0] == "-":
        if range == "\n":
            input_file = sys.stdin.readlines()
            userinput=True
        else:
            input_file = ""
    else:
        input_file = ""
        
    if range != "\n":
        if len(args) != 0:
            parser.error("extra operand: {0}")
        if "-" not in range:
            parser.error("invalid range: {0}\nmust be LO-HI")
        ind = range.find('-')

        if ind == 0 and len(range) == 1:
            arb = 0
        elif ind != -1:
            try:
                i1 = int(range[:ind])
            except:
                parser.error("invalid range: {0}\nmust be LO-HI")
            try:
                i2 = int(range[ind+1:])
            except:
                parser.error("invalid range: {0}\nmust be LO-HI")
            if i2 < i1 or i1 < 0 or i2 < 0:
                parser.error("invalid range: {0}\nmust be LO-HI")

        else:
            parser.error("invalid range: {0}\nmust be LO-HI")
            

    
    try:
        generator = randline(input_file, range, userinput, i1, i2)
        generator.printvals(rep, linecount, numlines)
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
