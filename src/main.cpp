//#include <iostream>//std in/out
#include <memory>//for smart pointers
#include <pqxx/pqxx>
#include <map>
#include "crud.cxx"

using namespace std;
using dbConnect = pqxx::connection;

//string getPeriodTypeId(string periodTypeName);
//string getPeriodId(string periodName, string containedById);
class opers{
public:
    static string getPeriodId(string periodName, string containedById="1"){
            some_crud::crud_t periodTypeId{"periodId"
                                        ,"BA.PERIOD"};

            periodTypeId.arg("periodName='"
                                +periodName
                                +"'"
                            )
                        .arg("containedById='"
                                +containedById
                                +"'"
                            );
            return some_crud::crud_opers::read(periodTypeId);
    };

    static string getPeriodTypeId(string periodTypeName){
            some_crud::crud_t periodTypeId{"periodTypeId"
                                        ,"BA.PERIOD_TYPE"};

            periodTypeId.arg("periodTypeName='"
                                    +periodTypeName
                                    +"'");
            return some_crud::crud_opers::read(periodTypeId);
        };
};

int	main(int argc, char **argv){
    some_crud::crud_t var1{"*", "TestTable"};
    var1.arg("first").arg("second").arg("third");
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
    /*cout << some_crud::crud_opers::create_method(var1) << endl;
    cout << some_crud::crud_opers::read(var1) << endl;
    var1.arg().arg().arg();
    cout << some_crud::crud_opers::read(var1) << endl;
    var1.table("BA.period").row("periodname='Декабрь'").arg("periodid = 12");
    cout << some_crud::crud_opers::update_method(var1) << endl;*/
//-------------------------------------------------------------
    
    cout << opers::getPeriodTypeId("Месяц") << endl;
    cout << opers::getPeriodTypeId("Год") << endl;
    cout << opers::getPeriodId("2023") << endl;
    cout << opers::getPeriodId("Январь", "3") << endl;
	return 0;
}

