Dianochka$# CREATE OR REPLACE FUNCTION trg_employees_salary_check_func()
Dianochka$# RETURNS TRIGGER AS
Dianochka$# $$
Dianochka-# BEGIN
Dianochka-#     IF OLD.salary > NEW.salary THEN
Dianochka-#         RAISE EXCEPTION 'Sorry! Salary can not be decreased!';
ОШИБКА:  ошибка синтаксиса (примерное положение: "$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_job_change
AFTER UPDATE OF job_id ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_log_job_change_func();-- ?R¤?RвRўЄ  в?бвRўле ¤ --ле
UPDATE employees SET job_id = 'CLERK', hire_date = '2023-01-01', department_id =
 10 WHERE id = 1;

-- ?Rб┐RваЁ┐ в?Єгйго ЁбвRаЁо (ЇгбвR)
SELECT * FROM job_history WHERE employee_id = 1;

-- ??-п?┐ ¤R<│-Rбвм
UPDATE employees SET job_id = 'SENIOR_CLERK' WHERE id = 1;

-- '┐RваЁ┐, звR ¤RЎ ўЁ<Rбм ў ЁбвRаЁо
SELECT * FROM job_history WHERE employee_id = 1;
-- ?│Ё¤ ?┐лc а?§г<мв в: R¤-  § ЇЁбм б employee_id=1, start_date=2023-01-01, end_
date=б??R¤-п, job_id=CLERK

-- ??-п?┐ ?йс а §
UPDATE employees SET job_id = 'MANAGER' WHERE id = 1;

-- '┐RваЁ┐ ЁбвRаЁо
SELECT * FROM job_history WHERE employee_id = 1;
-- ?│Ё¤ ?┐лc а?§г<мв в: ўвRа п § ЇЁбм б start_date = (Їа?¤л¤гйЁc end_date + 1)
commit;
DROP TRIGGER IF EXISTS trg_employee_manager_same_dept ON employees;
DROP FUNCTION IF EXISTS trg_employee_manager_same_dept_func();
DROP TRIGGER IF EXISTS trg_log_job_change ON employees;
DROP FUNCTION IF EXISTS trg_log_job_change_func();
drop table if exists job_history;
CREATE OR REPLACE FUNCTION trg_employees_salary_check_func()
RETURNS TRIGGER AS
$$")
LINE 1: $$ LANGUAGE plpgsql;
        ^
Dianochka=#     END IF;
ОШИБКА:  ошибка синтаксиса (примерное положение: "IF")
LINE 1: END IF;
            ^
Dianochka=#     RETURN NEW;
ОШИБКА:  ошибка синтаксиса (примерное положение: "RETURN")
LINE 1: RETURN NEW;
        ^
Dianochka=# END;
ПРЕДУПРЕЖДЕНИЕ:  нет незавершённой транзакции
COMMIT
Dianochka=# $$ LANGUAGE plpgsql;

















CREATE OR REPLACE FUNCTION trg_employees_salary_check_func()
RETURNS TRIGGER AS
$$
BEGIN
    IF OLD.salary > NEW.salary THEN
        RAISE EXCEPTION 'Sorry! Salary can not be decreased!';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;CREATE TRIGGER trg_employees_salary_check
BEFORE UPDATE ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_employees_salary_check_func();





DROP TRIGGER IF EXISTS trg_employee_manager_same_dept ON employees;DROP FUNCTION IF EXISTS trg_employee_manager_same_dept_func();DROP TRIGGER IF EXISTS trg_log_job_change ON employees;DROP FUNCTION IF EXISTS trg_log_job_change_func();DROP TABLE IF EXISTS job_history;
