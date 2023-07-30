//#include <iostream>//std in/out
#include <memory>//for smart pointers
#include <pqxx/pqxx>
#include <map>
#include "crud.cxx"

using namespace std;
using dbConnect = pqxx::connection;

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

/*class periodType{
    public:
    private:

}*/

int	main(int argc, char **argv){
    /*some_crud::crud_t crud{"*","SOME_TABLE"};
    cout << crud.table() << endl;
    crud.arg("TEST").arg("kek").arg("").arg("toot");*/
    /*dbConnect testConnection{"port=5433"};
    pqxx::work w(testConnection);

    pqxx::result res = w.exec("INSERT INTO BA.PERIOD VALUES(DEFAULT, (SELECT BA.getPeriodTypeId('Год')), '2025', (SELECT BA.PERIOD.PeriodId FROM BA.PERIOD WHERE periodname = 'general'))");
    res = w.exec("SELECT BA.addPeriod('Февраль', 'Месяц', '2023')");
    for (auto i:res){cout << "insert:"<< i[0] << endl;}
    res = w.exec("select * from BA.PERIOD");
    for (auto i:res){
        for (auto j:i){
            cout << j.name() << ": "<< j << " ";
        }
        cout << endl;
    }
    w.commit();
//    pqxx::row r = w.exec1("INSERT INTO BA.PERIOD VALUES(DEFAULT, (SELECT BA.getPeriodTypeId('Год')), '2025', (SELECT BA.PERIOD.PeriodId FROM BA.PERIOD WHERE periodname = 'general'))");    */
    //cout << some_crud::create_method(crud);
    crud_test();
	return 0;
}
