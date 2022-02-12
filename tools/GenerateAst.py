# File to generate subclasses for Production rules of Grammar for LOX
# Execution syntax python3 GenerateAst.py <.h path> <.cpp path> "<class_name> : <attr_type> <attr_identifier>"
# Execution Example: python3 GenerateAst.py ./tools_test ./tools_test "Grouping   : Expr* expression"

import sys

def writeToHFile(filePath, baseName, type):
    with open(filePath, 'w+') as f:

        content = \
f"#pragma once                      \n\
                                    \n\
#include \"./../Scanner/Token.h\"   \n\
#include \"./Expr.h\"               \n\
                                    \n\
class {baseName}                    \n\
{{                                  \n\
                                    \n\
}};                                 \n\
                                    \n\
                                    \n\
"

        f.write(content)

        f.close()
    pass

def defineAst(hPath, cppPath, baseName, type):
    # print(hPath, cppPath, baseName, type)
    writeToHFile(hPath + "/" + baseName + ".h", baseName, type)
    pass

hPath = sys.argv[1]
cppPath = sys.argv[2]
type = sys.argv[3]
baseName = type.split(":")[0].replace(" ", "")

defineAst(hPath, cppPath, baseName, type)