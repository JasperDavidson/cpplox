import os

def define_ast(output_dir, base_name, types):
    source_path = output_dir + "/" + base_name + ".cpp"
    source_file = open(os.path.expanduser(source_path), "w+")

    header_path = output_dir + "/" + base_name + ".h"
    header_file = open(os.path.expanduser(header_path), "w+")

    # Header guard begin and includes
    header_file.write("#ifndef EXPR_H\n#define EXPR_H\n\n")
    header_file.write("#include \"scanner.h\"\n")
    header_file.write("#include <variant>\n\n")

    # Include header file
    source_file.write("#include \"" + base_name + ".h\"\n")

    base_name = base_name.capitalize()

    # Define the variant type
    header_file.write("using expr_variant = std::variant<std::monostate, double, std::string>;\n\n")

    # Define base class
    header_file.write("template <typename T>\n")
    header_file.write("class " + base_name + " {\n")

    header_file.write("public:\n\t")
    for type in types:
        type_name = type.split("*")[0].strip()
        header_file.write("class " + type_name + ";\n\t")

    # Define abstract class to contain visitor methods --> To be implemented by each operation
    header_file.write("\n\tclass Visitor {\n")

    for type in types:
        type_name = type.split("*")[0].strip()
        header_file.write("\t\tvirtual T visit_" + type_name.lower() + "_" + base_name.lower() + "(const " + type_name + "& " + base_name.lower() + ");\n")

    header_file.write("\t};\n")

    header_file.write("\n\tvirtual T accept(const Visitor& visitor) const;\n")

    header_file.write("};\n")

    # Add all the required "types", implemented as derived classes
    for string in types: 
        source_file.write("\ntemplate <typename T>\n")
        header_file.write("\n")
        class_name = string.split("*")[0].strip()
        fields = string.split("*")[1].strip()
        define_type(source_file, header_file, base_name, class_name, fields)
        header_file.write("\n};\n")

    # Header guard end
    header_file.write("\n#endif")

def define_type(source_file, header_file, base_name, class_name, field_list):
    # Prepare the class definition
    header_file.write("template <typename T>\n")
    header_file.write("class " + base_name + "<T>::" + class_name + " : public " + base_name + "<T> {\n")
    fields = field_list.split(", ")

    # Write each field to the class as a... field
    header_file.write("public:\n")
    for field in fields:
        split_space = field.split(" ")
        header_file.write("\t")
        header_file.write("const " + split_space[0].strip() + "* " + split_space[1].strip() + ";")
        header_file.write("\n")
    header_file.write("\n\t")

    # Declare the constructor in the header file
    # header_file.write("\npublic:\n\t")
    header_file.write(class_name + "(")
    for i in range(len(fields)):
        field = fields[i].split(" ")
        header_file.write("const " + field[0].strip() + "* " + field[1].strip())

        if i < (len(fields) - 1):
            header_file.write(", ")

    header_file.write(");")

    # header_file.write(class_name + "(" + field_list + ");")

    # Define the constructor for the class in the source file
    source_file.write(base_name + "<T>::" + class_name + "::" + class_name + "(")

    for i in range(len(fields)):
        field = fields[i].split(" ")
        source_file.write("const " + field[0].strip() + "* " + field[1].strip())

        if i < (len(fields) - 1):
            source_file.write(", ")

    source_file.write(") : ")


    for i in range(len(fields)):
        field = fields[i].split(" ")[1]

        if i == 0:
            source_file.write(field + "(" + field + ")")
        else:
            source_file.write(", " + field + "(" + field + ")")

    source_file.write(" {};\n\n")

    # Declare the visitor accept method
    header_file.write("\n\n\tT " + "accept(const Visitor& visitor) const override;")

    # Define the visitor accept method
    source_file.write("template <typename T>\n")
    source_file.write("T " + base_name + "<T>::" + class_name + "::" + class_name + "::accept(const Visitor& visitor) const {\n")
    source_file.write("\tvisitor->visit_" + class_name.lower() + "_" + base_name.lower() + "(this);\n")
    source_file.write("};\n")

define_ast(os.path.dirname(os.path.abspath(__file__)), "expr", ["Binary*Expr left, Token operate, Expr right", "Grouping*Expr expression", "Literal*expr_variant value",
                                                                "Unary*Token operate, Expr right"])
