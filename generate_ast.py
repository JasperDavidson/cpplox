import os

def define_ast(output_dir, base_name, types):
    source_path = output_dir + "/" + base_name + ".cpp"
    source_file = open(os.path.expanduser(source_path), "w+")

    header_path = output_dir + "/" + base_name + ".h"
    header_file = open(os.path.expanduser(header_path), "w+")

    # Header guard begin
    header_file.write("#ifndef EXPR_H\n#define RUN_H\n\n")

    # Include header file
    source_file.write("#include \"" + base_name + ".h\"\n")

    base_name = base_name.capitalize()

    # Define base class
    header_file.write("template <typename T>\n")
    header_file.write("class " + base_name + " {\n\t")

    for type in types:
        type_name = type.split("*")[0].strip()
        header_file.write("class " + type_name + ";\n\t")

    # Define abstract class to contain visitor methods --> To be implemented by each operation
    header_file.write("\npublic:\n\tclass Visitor {\n")

    for type in types:
        type_name = type.split("*")[0].strip()
        header_file.write("\t\tvirtual T visit_" + type_name.lower() + "_" + base_name.lower() + "(" + type_name + " " + base_name.lower() + ");\n")

    header_file.write("\t};\n")

    header_file.write("\n\tvirtual T accept(Visitor* visitor);\n")

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
    for field in fields:
        header_file.write("\t")
        header_file.write("const " + field + ";")
        header_file.write("\n")

    # Declare the constructor in the header file
    header_file.write("\n public:\n\t")
    header_file.write(class_name + "(" + field_list + ");")

    # Define the constructor for the class in the source file
    source_file.write(base_name + "<T>::" + class_name + "::" + class_name + "(" + field_list + ") : ")
    for i in range(len(fields)):
        field = fields[i].split(" ")[1]

        if i == 0:
            source_file.write(field + "(" + field + ")")
        else:
            source_file.write(", " + field + "(" + field + ")")

    source_file.write(" {};\n\n")

    # Declare the visitor accept method
    header_file.write("\n\n\tT " + "accept(" + "Visitor* visitor) override;")

    # Define the visitor accept method
    source_file.write("template <typename T>\n")
    source_file.write("T " + base_name + "<T>::" + class_name + "::" + class_name + "::accept(Visitor* visitor) {\n")
    source_file.write("\tvisitor->visit_" + class_name.lower() + "_" + base_name.lower() + "(this);\n")
    source_file.write("};\n")

define_ast(os.path.dirname(os.path.abspath(__file__)), "expr", ["Test*int hello, int hi, double welcome", "TestTwo*double really, long hope, int this_works"])
