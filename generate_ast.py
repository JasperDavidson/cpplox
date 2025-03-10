import os

def define_ast(output_dir, base_name, types):
    source_path = output_dir + "/" + base_name + ".cpp"
    source_file = open(os.path.expanduser(source_path), "w+")

    header_path = output_dir + "/" + base_name + ".h"
    header_file = open(os.path.expanduser(header_path), "w+")

    source_file.write("#include \"" + base_name + ".h\"\n\n")

    base_name = base_name.capitalize()

    header_file.write("class " + base_name + " {\n\t\n")
    header_file.write("};\n");

    # Add all the required "types", implemented as derived classes
    for string in types: 
        header_file.write("\n")
        class_name = string.split(":")[0].strip()
        fields = string.split(":")[1].strip()
        define_type(source_file, header_file, base_name, class_name, fields)
        header_file.write("\n};")

def define_type(source_file, header_file, base_name, class_name, field_list):
    # Prepare the class definition
    header_file.write("class " + class_name + " : " + base_name + " {\n")
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
    source_file.write(class_name + "::" + class_name + "(" + field_list + ") : ")
    for i in range(len(fields)):
        field = fields[i].split(" ")[1]

        if i == 0:
            source_file.write(field + "(" + field + ")")
        else:
            source_file.write(", " + field + "(" + field + ")")

    source_file.write(" {};")

define_ast(os.path.dirname(os.path.abspath(__file__)), "expr", ["Test:int hello, int hi, double welcome"]);
