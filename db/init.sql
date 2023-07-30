CREATE SCHEMA BA;
------------------------------------------------------------------------------------
--тип статьи, например: расход, доход, инвестиция, долг-----------------------------
CREATE TABLE IF NOT EXISTS BA.EXPENSE_TYPE(
    ExpenseTypeId           SERIAL UNIQUE NOT NULL,
    ExpenseTypeName         VARCHAR(64) UNIQUE NOT NULL,
    ExpenseTypeDescription  TEXT
);
-------------------------------------------------------------------------------------
--непосредственно статья, например: развлечения, зарплата, покупка активов-----------
CREATE TABLE IF NOT EXISTS BA.EXPENSES(
    ExpenseId           SERIAL UNIQUE NOT NULL,
    ExpenseName         VARCHAR(64) UNIQUE NOT NULL,
    ExpenseType         INTEGER REFERENCES BA.EXPENSE_TYPE(ExpenseTypeId) NOT NULL,
    ExpenseDescription  TEXT
);

-------------------------------------------------------------------------------------
--добавить поле с возможными значениями
CREATE TABLE IF NOT EXISTS BA.PERIOD_TYPE(
    PeriodTypeId    SERIAL UNIQUE NOT NULL,
    PeriodTypeName  VARCHAR(64) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS BA.PERIOD(
    PeriodId            SERIAL UNIQUE NOT NULL,
    PeriodType          INTEGER REFERENCES BA.PERIOD_TYPE(PeriodTypeId) NOT NULL,
    PeriodName          VARCHAR(64) NOT NULL,
    ContainedById       INTEGER REFERENCES BA.PERIOD(PeriodId) NOT NULL,
    UNIQUE (PeriodName, ContainedById)
);

--Нужен триггер, который будет проверять уникальность 
--Если вставляется тип периода == год
--CREATE TRIGGER BEFORE INSERT ON BA.PERIOD

--Нужно само поле, которое вяжется на имеющиеся поля и 
--содержит значение

CREATE TABLE IF NOT EXISTS BA.RECORDS(
    RecordId        SERIAL UNIQUE NOT NULL,
    PeriodId        INTEGER REFERENCES BA.PERIOD(PeriodId) NOT NULL,
    ExpenseId       INTEGER REFERENCES BA.EXPENSES(ExpenseId) NOT NULL,
    RecordValue     text NOT NULL,
    RecordComment   text
);


