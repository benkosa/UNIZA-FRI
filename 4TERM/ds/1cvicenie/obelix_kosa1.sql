
-- jednoriadkovy komentar
/*
    viacriadkovy komentar
*/

select table_name 
    from tabs;
    
/* kategorizovane informacie v oracle
- tables info o tabulkac
- indexes info o indexoxh
...
*/
    
/* prefixy 
- user objekty ktoreyvh vlastnikom som ja
- all vlastnikom som ja elbo mam k nim prstup
- dba vsetky szstemove tabulky vsetkyych uzivatelov, prutup ma len administrator
*/

select table_name from user_tables;

--vracia strukturu tabulky ktoru si zvolime
desc user_tables;

desc student;

-- ak sa primarny kluc sklada z dvoch atributov ide o KOMPOZITNY pk
--CUDZI kluc sluzi pre propojenie tabuliek

--chceme si vybrat atributy z osobnych udajov
desc os_udaje;
--vsetku osoby ktore sa nachadzaju v rabulke
select meno, priezvisko, rod_cislo
    from os_udaje;
    
--specialna tabulka DUAL
--sluzi na zistenie prihalesneho pouzivatela, systemovy cas..
desc dual;
--vrati hodnotu x
select dummy from dual;

--vrati prihlaseneho uzivatela
select user from dual;

--je mozne pristupit aj k tabulkam ktore niesu moje ale musim na ne mat pravo
-- * znamena vsetko
select * from kvet3.osoba;


--BLOK PRIKAZOV
declare
    cislo integer;
begin
cislo := 5;
    dbms_output.put_line('Ahoj ' || cislo);
end;
/

set serveroutput on;

    