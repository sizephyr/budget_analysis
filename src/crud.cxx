#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
                        result += result.empty() ? i : (separator + i);
                return result;
            }
            string get_args(){return get_args(" AND ");}//default separator is "AND"

            crud_t& table(string input){//set table name
                if (!input.empty())
                    _table = input;
                return *this;
            }
            string table(){//get table name
                return _table.empty()? "" : _table;
            }

            crud_t& row(string input){//set row name
                _row = input.empty() ? "*" : input;
                return *this;
            }
            string row(){//get row name
                return _row;
            }
    };

    class crud_opers{
    //const string _create {"CREATE"};
        public:

            static string create_method(crud_t crud){
                string args = move(crud.get_args(", "));
                string result{""};
                if (!args.empty())
                    result =
                        "CREATE INTO "
                        + crud.table()
                        + " VALUES (DEFAULT, "
                        + args
                        + ")";
                //cout << "Args is |" << args << "|"<< endl;
                return result;
            };

            const string _read {"SELECT"};
            static string read(crud_t crud){
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
                        (" where " + args)
                    )
                };
                return result;
            };
            const string _update {"UPDATE"};
            static string update_method(crud_t crud){
                string args = move(crud.get_args());
                string row = move(crud.row());
                string table = move(crud.table());
                string result {""};
                if (
                        !table.empty() 
                        && !row.empty()
                        && !args.empty()
                    )
                    result = 
                        "UPDATE "
                        + crud.table()
                        + " SET "
                        + crud.row()
                        + (
                            args.empty()
                            ?
                            ""
                            :
                            (" where " + args)
                        )
                    ;
                else
                    cout << "crud::crud_opers::update_method\n\t"
                        << "ERR: one or more required parameters are empty!\n";
                return result.empty() ? "" : result;
            };
            const string _delete {"DELETE"};
      };
};
