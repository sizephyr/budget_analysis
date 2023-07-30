------------------------------------------------------------------------------------
--------типы статьи расхода/дохода--------------------------------------------------

INSERT INTO BA.EXPENSE_TYPE VALUES(DEFAULT, 'Доход', 'Классические доходы');
-----------------------------
INSERT INTO BA.EXPENSE_TYPE VALUES(DEFAULT, 'Расход', 'Классические расходы');
-----------------------------
INSERT INTO BA.EXPENSE_TYPE VALUES(DEFAULT, 'Инвестиции', 'Классические инвестиции');
-----------------------------
INSERT INTO BA.EXPENSE_TYPE VALUES(DEFAULT, 'Долги', '');
-----------------------------
-------------------------------------------------------------------------------------
--непосредственно статья, например: развлечения, зарплата, покупка активов-----------
--расходы
SELECT '--------------РАСХОДЫ--------------' AS PART;
--SELECT addExpense('') AS id, '' AS name;
SELECT BA.addExpense('здоровье и красота') AS id, 'здоровье и красота' AS name;
SELECT BA.addExpense('образование') AS id, 'образование' AS name;
SELECT BA.addExpense('развлечения') AS id, 'развлечения' AS name;
SELECT BA.addExpense('туризм, путешествия') AS id, 'туризм, путешествия' AS name;
SELECT BA.addExpense('продукты и хозтовары') AS id, 'продукты и хозтовары' AS name;
SELECT BA.addExpense('квартплата') AS id, 'квартплата' AS name;
SELECT BA.addExpense('интернет и связь') AS id, 'интернет и связь' AS name;
SELECT BA.addExpense('аренда жилья') AS id, 'аренда жилья' AS name;
SELECT BA.addExpense('непредвиденное, ремонт') AS id, 'непредвиденное, ремонт' AS name;
SELECT BA.addExpense('одежда, товары') AS id, 'одежда, товары' AS name;
SELECT BA.addExpense('цифровые покупки') AS id, 'цифровые покупки' AS name;
SELECT BA.addExpense('крупные траты') AS id, 'крупные траты' AS name;
SELECT BA.addExpense('чрезмерное потребление') AS id, 'чрезмерное потребление' AS name;
--доходы
SELECT '--------------ДОХОДЫ--------------' AS PART;
--SELECT addIncome('') AS id, '' AS name;
SELECT BA.addIncome('зарплата') AS id, 'зарплата' AS name;
SELECT BA.addIncome('подработка') AS id, 'подработка' AS name;
SELECT BA.addIncome('дивиденды и купоны') AS id, 'дивиденды и купоны' AS name;
SELECT BA.addIncome('депозиты') AS id, 'депозиты' AS name;
SELECT BA.addIncome('продажа имущетва') AS id, 'продажа имущетва' AS name;
--инвестиции
SELECT '--------------ИНВЕСТИЦИИ--------------' AS PART;
--SELECT addInvest('') AS id, '' AS name;
SELECT BA.addInvest('НПФ') AS id, 'НПФ' AS name;
SELECT BA.addInvest('инвестиции') AS id, 'инвестиции' AS name;
SELECT BA.addInvest('экстренный бюджет') AS id, 'экстренный бюджет' AS name;
SELECT BA.addInvest('остаток в конце месяца') AS id, 'остаток в конце месяца' AS name;
--долги
SELECT '--------------ДОЛГИ--------------' AS PART;
--SELECT addDebt('') AS id, '' AS name;
SELECT addDebt('кредит') AS id, 'кредит' AS name;
SELECT addDebt('рассрочка') AS id, 'рассрочка' AS name;
SELECT addDebt('долг') AS id, 'долг' AS name;
-------------------------------------------------------------------------------------
-------------------периоды-----------------------------------------------------------
INSERT INTO BA.PERIOD_TYPE VALUES (DEFAULT, 'general');
INSERT INTO BA.PERIOD_TYPE VALUES (DEFAULT, 'Год');
INSERT INTO BA.PERIOD_TYPE VALUES (DEFAULT, 'Месяц');

INSERT INTO BA.PERIOD VALUES (DEFAULT, (SELECT BA.getPeriodTypeId('general')), 'general', 1);

--INSERT INTO BA.PERIOD VALUES (
  --  DEFAULT,
    --(
      --  SELECT BA.PERIOD_TYPE.PeriodTypeId
        --    FROM BA.PERIOD_TYPE
          --  WHERE BA.PERIOD_TYPE.PeriodTypeName = 'Год'
    --),
    --'2023',0
--);
--пример вставки месяца
--INSERT INTO BA.PERIOD VALUES (
  --  DEFAULT,
    --(
      --  SELECT BA.PERIOD_TYPE.PeriodTypeId
        --    FROM BA.PERIOD_TYPE
          --  WHERE BA.PERIOD_TYPE.PeriodTypeName = 'Месяц'
--    ),
  --  'Январь',
    --(
      --  SELECT BA.PERIOD_TYPE.PeriodTypeId
        --    FROM BA.PERIOD_TYPE
          --  WHERE BA.PERIOD_TYPE.PeriodTypeName = 'Год')
--);
