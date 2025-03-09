import os

def define_ast(output_dir, base_name, types):
    path = output_dir + "/" + base_name + ".cpp"
    file = open(os.path.expanduser(path), "w+")

    # Define the overal all base class
    file.write("class " + base_name + " {\n\t\n")
    file.write("};\n");

    # Add all the required "types", implemented as derived classes
    for string in types: 
        file.write("\n")
        class_name = string.split(":")[0].strip()
        fields = string.split(":")[1].strip()
        define_type(file, base_name, class_name, fields)
        file.write("\n};")

def define_type(file, base_name, class_name, field_list):
    # Prepare the class definition
    file.write("class " + class_name + " : " + base_name + " {\n")
    fields = field_list.split(", ")
   
    # Write each field to the class as a... field
    for field in fields:
        file.write("\t")
        file.write("const " + field + ";")
        file.write("\n")

    file.write("\n public:\n\t")
    file.write(class_name + "(" + field_list + ") : ")

    # Define the constructor for the class
    for i in range(len(fields)):
        field = fields[i].split(" ")[1]

        if i == 0:
            file.write(field + "(" + field + ")")
        else:
            file.write(", " + field + "(" + field + ")")

    file.write(" {};")

define_ast(os.path.dirname(os.path.abspath(__file__)), "Expr", ["test:int hello, int hi, double welcome"]);
