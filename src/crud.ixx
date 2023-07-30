export module crud;

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
