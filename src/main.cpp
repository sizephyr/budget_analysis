#include <iostream>//std in/out
#include <memory>//for smart pointers
#include <pqxx/pqxx>
#include <map>
#include <algorithm>

using namespace std;
using dbConnect = pqxx::connection;


//SELECT 1.ROW1, 1.ROW2, 1.ROW1
//  FROM 1 
//  WHERE 

namespace some_crud{
    class crud_t{
        private:
            string          _row;
            string          _table;
            vector<string>  _args;

        public:
            crud_t():_row("*"),_table(""){}
            crud_t(string row):_row(row),_table(""){}
            crud_t(string row, string table):_row(row),_table(table){}
            crud_t(string row, string table, vector<string> args):
                _row(row)
                ,_table(table)
                ,_args(args)
        {}

            crud_t& arg(string input){//add arg
                if (!input.empty())
                    _args.push_back(input);
                return *this;
            }
            crud_t& arg(){//remove arg
                if (!_args.empty())
                    _args.pop_back();
                return *this;
            }
            string get_args(string separator){//get arguments with especially separator
                string result;
                for (auto i:_args)
                    if (!i.empty())
                        result += result.empty() ? i : (" "+separator+" " + i);
                return result;
            }
            string get_args(){return get_args("AND");}//default separator is "AND"

            void table(string input){//set table name
                if (!input.empty())
                    _table = input;
            }
            string table(){//get table name
                return _table.empty()? "" : _table;
            }

            void row(string input){//set row name
                _row = input.empty() ? "*" : input;
            }
            string row(){//get row name
                return _row;
            }
    };

    //const string _create {"CREATE"};
        string create_method(crud_t crud){
            string args = move(crud.get_args(","));
            string result{""};
            if (!args.empty())
                result =  
                    "CREATE INTO " 
                    + crud.table() 
                    + " VALUES (DEFAULT, "
                    + args
                    + ")";
            cout << "Args is |" << args << "|"<< endl;
            return result;
        };

        const string _read {"SELECT"};
        string read(crud_t crud){
            string args = crud.get_args();
            string result{
                "SELECT "
                + crud.row()
                + " FROM "
                + crud.table()
                + (
                    args.empty()
                    ?
                    ""
                    :
                    (" where" + args)
                )
            };
            return result;
        };
        const string _update {"UPDATE"};
        const string _delete {"DELETE"};
};

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
