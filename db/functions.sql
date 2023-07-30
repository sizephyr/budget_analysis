--------родительская функция добавления значения в статьи--------------------------
CREATE FUNCTION BA.addToExpenses(ExpenseNameArg text, ExpenseTypeNameArg text) RETURNS text AS $$
    #variable_conflict use_variable
    DECLARE result          TEXT;
    DECLARE ExpenseTypeVar  INTEGER;
    BEGIN
        --получаем айди целевого типа
        ExpenseTypeVar := (
            SELECT BA.EXPENSE_TYPE.ExpenseTypeId
                FROM BA.EXPENSE_TYPE
                WHERE BA.EXPENSE_TYPE.ExpenseTypeName = ExpenseTypeNameArg);
        INSERT INTO BA.EXPENSES VALUES(
            --BA.EXPENSES.ExpenseId
            DEFAULT,
            --BA.EXPENSES.ExpenseName
            ExpenseNameArg,
            --BA.EXPENSES.ExpenseType
            ExpenseTypeVar,
            --BA.EXPENSES.ExpenseDescription
            '');
        result := (
            SELECT BA.EXPENSES.ExpenseId
                FROM BA.EXPENSES
                WHERE ExpenseName = ExpenseNameArg
                    AND ExpenseType = ExpenseTypeVar);
        return result;
    END;
$$ LANGUAGE plpgsql;

SELECT 'addToExpenses' AS CREATED_FNC;

--------------дочерние функции добавления значения в статьи--------------------------
--добавить доход
CREATE FUNCTION BA.addIncome(Name TEXT) RETURNS text AS $$
    SELECT BA.addToExpenses(Name, 'Доход'::text);
$$ LANGUAGE sql;

SELECT 'addIncome' AS CREATED_FNC;
--добавить расход
CREATE FUNCTION BA.addExpense(Name TEXT) RETURNS text AS $$
    SELECT BA.addToExpenses(Name, 'Расход'::text);
$$ LANGUAGE sql;

SELECT 'addExpense' AS CREATED_FNC;
--добавить инвестицию
CREATE FUNCTION BA.addInvest(Name TEXT) RETURNS text AS $$
    SELECT BA.addToExpenses(Name, 'Инвестиции'::text);
$$ LANGUAGE sql;

SELECT 'addInvest' AS CREATED_FNC;
--добавить долг
CREATE FUNCTION BA.addDebt(Name TEXT) RETURNS text AS $$
    SELECT BA.addToExpenses(Name, 'Долги'::text);
$$ LANGUAGE sql;

SELECT 'addDebt' AS CREATED_FNC;
-------------------------------------------------------------------------------------

--INSERT INTO BA.PERIOD VALUES (
  --  DEFAULT,
    --(
      --  SELECT BA.PERIOD_TYPE.PeriodTypeId
        --    FROM BA.PERIOD_TYPE
          --  WHERE BA.PERIOD_TYPE.PeriodTypeName = 'Год'
--    ),
  --  '2023'
--);

CREATE FUNCTION BA.getPeriodTypeId(PeriodTypeNameArg text) RETURNS INTEGER AS $$
    SELECT BA.PERIOD_TYPE.PeriodTypeId
        FROM BA.PERIOD_TYPE
        WHERE BA.PERIOD_TYPE.PeriodTypeName = PeriodTypeNameArg;
$$ LANGUAGE sql;

CREATE FUNCTION BA.getPeriodId(PeriodNameArg text, PeriodContainedByIdVar  INTEGER) RETURNS INTEGER AS $$
    SELECT BA.PERIOD.PeriodId
        FROM BA.PERIOD
        WHERE PeriodName = PeriodNameArg
            --AND PeriodType = PeriodTypeIdVar;
            AND ContainedById = PeriodContainedByIdVar;
$$ LANGUAGE sql;
---------Родительская функция добавления периодов, основная зона видимости: год и месяц
CREATE FUNCTION BA.addPeriod(PeriodNameArg text, PeriodTypeNameArg text, PeriodContainedByNameArg text) RETURNS text AS $$
    #variable_conflict use_variable
    DECLARE 
        result                  TEXT;
        PeriodTypeIdVar         INTEGER;
        PeriodContainedByIdVar  INTEGER;
        GeneralPeriodId         INTEGER;
    BEGIN
        --получаем айди целевого типа
        PeriodTypeIdVar := (SELECT BA.getPeriodTypeId(PeriodTypeNameArg));
        --id коневого периода
        GeneralPeriodId := (SELECT BA.PERIOD.PeriodId FROM BA.PERIOD WHERE periodname = 'general');
        --id содержащего периода
        PeriodContainedByIdVar := (SELECT BA.getPeriodId(PeriodContainedByNameArg, GeneralPeriodId));
        IF PeriodContainedByIdVar IS NULL THEN PeriodContainedByIdVar := GeneralPeriodId;END IF;
        IF PeriodTypeIdVar IS NOT NULL THEN
            result := (SELECT BA.getPeriodId(PeriodNameArg, PeriodContainedByIdVar));
            IF result IS NULL AND (--добавить сообщение, что отсутствует год, если вставляется месяц в отсутствующий год
                (PeriodContainedByIdVar = GeneralPeriodId AND PeriodTypeNameArg = 'Год') 
                OR 
                NOT (PeriodContainedByIdVar = GeneralPeriodId)
                ) THEN
                INSERT INTO BA.PERIOD VALUES(
                    --BA.PERIOD.PeriodId
                    DEFAULT,
                    --BA.PERIOD.PeriodType
                    PeriodTypeIdVar,
                    --BA.PERIOD.PeriodName
                    PeriodNameArg,
                    --BA.PERIOD.ContainedByType
                    PeriodContainedByIdVar);
                result := (SELECT BA.getPeriodId(PeriodNameArg, PeriodContainedByIdVar));
            END IF;
        ELSE
            result := (
            SELECT 'PeriodType IS NOT AVAILABLE' AS ERR);
        END IF;
        return result;
    END;
$$ LANGUAGE plpgsql;

--CREATE TYPE BA.months AS ENUM (
  --  'Январь','Февраль', 'Март',
    --'Апрель','Май','Июнь','Июль',
    --'Август','Сентябрь','Октябрь',
    --'Ноябрь','Декабрь');
--костыль для проверки значений вставляемых месяцев
CREATE TABLE BA.months (
    month   VARCHAR(8) UNIQUE NOT NULL
);
INSERT INTO BA.months VALUES('Январь');
INSERT INTO BA.months VALUES('Февраль');
INSERT INTO BA.months VALUES('Март');
INSERT INTO BA.months VALUES('Апрель');
INSERT INTO BA.months VALUES('Май');
INSERT INTO BA.months VALUES('Июнь');
INSERT INTO BA.months VALUES('Июль');
INSERT INTO BA.months VALUES('Август');
INSERT INTO BA.months VALUES('Сентябрь');
INSERT INTO BA.months VALUES('Октябрь');
INSERT INTO BA.months VALUES('Ноябрь');
INSERT INTO BA.months VALUES('Декабрь');
--функция вставки месцев с использованием функции BA.addMonth
CREATE FUNCTION BA.addMonth(monthName text, yearName text) RETURNS TEXT AS $$
    DECLARE
        result  TEXT;
    BEGIN
        IF (SELECT BA.months.month FROM BA.months WHERE BA.months.month = monthName) IS NOT NULL THEN
            result := (SELECT BA.addPeriod(monthName,'Месяц',yearName));
        ELSE
            result := (SELECT 'Такого месяца не существует');
        END IF;
        return result;
    END;
$$ LANGUAGE plpgsql;

