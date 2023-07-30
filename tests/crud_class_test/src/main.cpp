#include "../../../src/crud.cxx"

void crud_test(){
    some_crud::crud_t test1;

    cout << "TEST: crud_test empty construct:"
            << "\n\ttest1.row():\t\t"
            << test1.row()
            << "\n\ttest1.table():\t\t|"
            << test1.table()
            << "|\n\ttest1.get_args():\t|"
            << test1.get_args()
            << "|\n\ttest1.get_args(\",\"):\t|"
            << test1.get_args(",")
            << "|\n\ttest1.arg(\"lol\").arg(\"\").arg(\"kek\")";
    test1.arg("lol").arg("").arg("kek");
    cout << "\n\ttest1.get_args():\t|"
            << test1.get_args()
            << "|\n\ttest1.get_args(\",\"):\t|"
            << test1.get_args(",")
            << "|\n\ttest1.arg().arg().arg()";
    test1.arg().arg().arg();
    cout << "\n\ttest1.get_args():\t|"
            << test1.get_args()
            << "|\n\ttest1.get_args(\",\"):\t|"
            << test1.get_args(",")
            << "|\n\ttest1.row(\"SOME_ROW\")";
    test1.row("SOME_ROW");
    cout << "\n\ttest1.row():\t\t|"
            << test1.row()
            << "|\n\ttest1.row(\"SOME_ROW_REWRITE\")";
    test1.row("SOME_ROW_REWRITE");
    cout << "\n\ttest1.row():\t\t|"
            << test1.row()
            << "|\n\ttest1.row(\"\")";
    test1.row("");
    cout << "\n\ttest1.row():\t\t|"
            << test1.row()
            << "\n\ttest1.table(\"SOME_TABLE\"):\t\t|";
    test1.table("SOME_TABLE");
    cout << "\n\ttest1.table():\t\t|"
            << test1.table()
            << "\n\ttest1.table(\"\"):\t\t|";
    test1.table("");
    cout << "\n\ttest1.table():\t\t|"
            << test1.table();
}

int	main(int argc, char **argv){
    crud_test();
	return 0;
}
