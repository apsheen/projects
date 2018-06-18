from __future__ import print_function

import inspect
import re
import sys

from distutils.sysconfig import get_python_lib
from os.path import abspath, join
from termcolor import colored
from traceback import extract_tb, format_list, format_exception_only, format_exception


"""class flushfile():
    Disable buffering for standard output and standard error.
    http://stackoverflow.com/a/231216

    def __init__(self, f):
        self.f = f

    def __getattr__(self, name):
        return object.__getattribute__(self.f, name)

    def write(self, x):
        self.f.write(x)
        self.f.flush()


sys.stderr = flushfile(sys.stderr)
sys.stdout = flushfile(sys.stdout)"""

class userInput():
    def get_string(prompt=None):
        """
        Read a line of text from standard input and return it as a string,
        sans trailing line ending. Supports CR (\r), LF (\n), and CRLF (\r\n)
        as line endings. If user inputs only a line ending, returns "", not None.
        Returns None upon error or no input whatsoever (i.e., just EOF). Exits
        from Python altogether on SIGINT.
        """
        try:
            if prompt is not None:
                print(prompt, end="")
            s = sys.stdin.readline()
            if not s:
                return None
            return re.sub(r"(?:\r|\r\n|\n)$", "", s)
        except KeyboardInterrupt:
            sys.exit("")
        except ValueError:
            return None