# File to generate subclasses for Production rules of Grammar for LOX
# Execution syntax python3 GenerateAst.py <.h path> <.cpp path> "<class_name> : <attr_type> <attr_identifier>"
# Execution Example: python3 GenerateAst.py ./tools_test ./tools_test "Grouping   : Expr* expression Token* operator_"

from ast import arg
import sys

from click import argument

def writeToHFile(filePath, baseName, type):
    with open(filePath, 'w+') as f:
        classAttrs = type.split(":")[1].split(" ")
        classAttrs = [a for a in classAttrs if a not in ['']]

        attrString = ""
        argumentString = ""

        i = 0
        while i < len(classAttrs):
            attrString += classAttrs[i] + " " + classAttrs[i + 1] + ";  \n\t\t"
            argumentString += classAttrs[i] + " " + classAttrs[i + 1] + ", "
            i += 2

        argumentString = argumentString[0: -2]    

        content = \
f"#pragma once                          \n\
                                        \n\
#include \"./../Scanner/Token.h\"       \n\
#include \"./Expr.h\"                   \n\
                                        \n\
class {baseName} : public Expr          \n\
{{                                      \n\
    public:                             \n\
        {attrString}                    \n\
    public:                             \n\
        {baseName}({argumentString});   \n\
}};                                     \n\
"

        f.write(content)

        f.close()

        print(f"{baseName}.h created.")
    pass

def writeToCppFile(filePath, baseName, type):
    with open(filePath, 'w+') as f:
        classAttrs = type.split(":")[1].split(" ")
        classAttrs = [a for a in classAttrs if a not in ['']]

        bodyString = ""
        argumentString = ""

        i = 0
        while i < len(classAttrs):
            argumentString += classAttrs[i] + " " + classAttrs[i + 1] + ", "
            bodyString += f"this->{classAttrs[i + 1]} = {classAttrs[i + 1]};\n\t"
            i += 2

        argumentString = argumentString[0: -2]    

        content = \
f"#include \"./../../include/Parser/{baseName}.h\"      \n\
                                                        \n\
{baseName}::{baseName}({argumentString})                \n\
{{                                                      \n\
    {bodyString}                                        \n\
}};                                                     \n\
"
        f.write(content)

        f.close()

        print(f"{baseName}.cpp created.")
    pass

def defineAst(hPath, cppPath, baseName, type):
    # print(hPath, cppPath, baseName, type)
    writeToHFile(hPath + "/" + baseName + ".h", baseName, type)
    writeToCppFile(cppPath + "/" + baseName + ".cpp", baseName, type)
    pass

hPath = sys.argv[1]
cppPath = sys.argv[2]
type = sys.argv[3]
baseName = type.split(":")[0].replace(" ", "")

defineAst(hPath, cppPath, baseName, type)