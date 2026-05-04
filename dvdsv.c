ianochka=# CREATE OR REPLACE FUNCTION trg_employee_manager_same_dept_func()
Dianochka-# RETURNS TRIGGER AS
Dianochka-# $$
Dianochka$# DECLARE
Dianochka$#     manager_dept_id INTEGER;
Dianochka$# BEGIN
Dianochka$#     SELECT department_id INTO manager_dept_id
Dianochka$#     FROM employees
Dianochka$#     WHERE id = NEW.manager;
Dianochka$#
Dianochka$#     IF manager_dept_id != NEW.department_id THEN
Dianochka$#         RAISE EXCEPTION 'Employee and manager must belong to the sam
e department';
Dianochka$#     END IF;
Dianochka$#
Dianochka$#     RETURN NEW;
Dianochka$# END;
Dianochka$# CREATE TRIGGER trg_employee_manager_same_dept
Dianochka$# BEFORE INSERT OR UPDATE OF department_id, manager ON employees
Dianochka$# FOR EACH ROW
Dianochka$# EXECUTE FUNCTION trg_employee_manager_same_dept_func();
Dianochka$#
Dianochka$# CREATE OR REPLACE FUNCTION trg_employee_manager_same_dept_func()
Dianochka$# RETURNS TRIGGER AS
Dianochka$# $$
Dianochka-# DECLARE
Dianochka-#     manager_dept_id INTEGER;
ОШИБКА:  ошибка синтаксиса (примерное положение: "DECLARE")
LINE 25: DECLARE
         ^
Dianochka=# BEGIN
Dianochka-#     SELECT department_id INTO manager_dept_id
Dianochka-#     FROM employees
Dianochka-#     WHERE id = NEW.manager;
ОШИБКА:  ошибка синтаксиса (примерное положение: "SELECT")
LINE 2:     SELECT department_id INTO manager_dept_id
            ^
Dianochka=#
Dianochka=#     IF manager_dept_id != NEW.department_id THEN
Dianochka-#         RAISE EXCEPTION 'Employee and manager must belong to the sam
e department';
ОШИБКА:  ошибка синтаксиса (примерное положение: "IF")
LINE 1: IF manager_dept_id != NEW.department_id THEN
        ^
Dianochka=#     END IF;
ОШИБКА:  ошибка синтаксиса (примерное положение: "IF")
LINE 1: END IF;
            ^
Dianochka=#
Dianochka=#     RETURN NEW;
ОШИБКА:  ошибка синтаксиса (примерное положение: "RETURN")
LINE 1: RETURN NEW;
        ^
Dianochka=# END;
ПРЕДУПРЕЖДЕНИЕ:  нет незавершённой транзакции
COMMIT
Dianochka=# $$ LANGUAGE plpgsql;
Dianochka$# CREATE TRIGGER trg_employee_manager_same_dept
Dianochka$# BEFORE INSERT OR UPDATE OF department_id, manager ON employees
Dianochka$# FOR EACH ROW
Dianochka$# EXECUTE FUNCTION trg_employee_manager_same_dept_func();
Dianochka$# -- Подготовка тестовых данных
Dianochka$# UPDATE employees SET department_id = 10, manager = NULL WHERE id = 1
;
Dianochka$# UPDATE employees SET department_id = 20, manager = 1 WHERE id = 2;
Dianochka$# UPDATE employees SET department_id = 10, manager = 1 WHERE id = 3;
Dianochka$#
Dianochka$# -- НЕЛЬЗЯ — менеджер из другого отдела (сотрудник id=3 в отделе 10,
менеджер id=2 в отделе 20)
Dianochka$# UPDATE employees SET manager = 2 WHERE id = 3;
Dianochka$# -- Ожидаемая ошибка: ERROR: Employee and manager must belong to the
same department
Dianochka$#
Dianochka$# -- МОЖНО — менеджер из того же отдела (id=1 в отделе 10)
Dianochka$# UPDATE employees SET manager = 1 WHERE id = 3;
Dianochka$# -- Ожидаемый результат: успешно
Dianochka$#
Dianochka$# CREATE TABLE IF NOT EXISTS job_history (
Dianochka$#     employee_id INTEGER,
Dianochka$#     start_date DATE,
Dianochka$#     end_date DATE,
Dianochka$#     job_id VARCHAR(20),
Dianochka$#     department_id INTEGER
Dianochka$# );CREATE OR REPLACE FUNCTION trg_log_job_change_func()
Dianochka$# RETURNS TRIGGER AS
Dianochka$# $$
Dianochka-# DECLARE
Dianochka-#     v_enddate DATE;
ОШИБКА:  ошибка синтаксиса (примерное положение: "$$ LANGUAGE plpgsql;
CREATE TRIGGER trg_employee_manager_same_dept
BEFORE INSERT OR UPDATE OF department_id, manager ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_employee_manager_same_dept_func();
-- ?R¤?RвRўЄ  в?бвRўле ¤ --ле
UPDATE employees SET department_id = 10, manager = NULL WHERE id = 1;
UPDATE employees SET department_id = 20, manager = 1 WHERE id = 2;
UPDATE employees SET department_id = 10, manager = 1 WHERE id = 3;

-- ?:<?╪? - ┐?-?¤│?а Ё§ ¤аг?R?R Rв¤?<  (бRваг¤-ЁЄ id=3 ў Rв¤?<? 10, ┐?-?¤│?а id=
2 ў Rв¤?<? 20)
UPDATE employees SET manager = 2 WHERE id = 3;
-- ?│Ё¤ ?┐ п RиЁЎЄ : ERROR: Employee and manager must belong to the same departm
ent

-- ??┼?? - ┐?-?¤│?а Ё§ вR?R │? Rв¤?<  (id=1 ў Rв¤?<? 10)
UPDATE employees SET manager = 1 WHERE id = 3;
-- ?│Ё¤ ?┐лc а?§г<мв в: гбЇ?и-R

CREATE TABLE IF NOT EXISTS job_history (
    employee_id INTEGER,
    start_date DATE,
    end_date DATE,
    job_id VARCHAR(20),
    department_id INTEGER
);CREATE OR REPLACE FUNCTION trg_log_job_change_func()
RETURNS TRIGGER AS
$$")
LINE 1: $$ LANGUAGE plpgsql;
        ^
Dianochka=#     v_startdate DATE;
ОШИБКА:  ошибка синтаксиса (примерное положение: "v_startdate")
LINE 1: v_startdate DATE;
        ^
Dianochka=# BEGIN
Dianochka-#     SELECT MAX(end_date) INTO v_enddate
Dianochka-#     FROM job_history
Dianochka-#     WHERE employee_id = OLD.id;
ОШИБКА:  ошибка синтаксиса (примерное положение: "SELECT")
LINE 2:     SELECT MAX(end_date) INTO v_enddate
            ^
Dianochka=#
Dianochka=#     IF v_enddate IS NULL THEN
Dianochka-#         v_startdate := OLD.hire_date;
ОШИБКА:  ошибка синтаксиса (примерное положение: "IF")
LINE 1: IF v_enddate IS NULL THEN
        ^
Dianochka=#     ELSE
Dianochka-#         v_startdate := v_enddate + 1;
ОШИБКА:  ошибка синтаксиса (примерное положение: "ELSE")
LINE 1: ELSE
        ^
Dianochka=#     END IF;
ОШИБКА:  ошибка синтаксиса (примерное положение: "IF")
LINE 1: END IF;
            ^
Dianochka=#
Dianochka=#     INSERT INTO job_history (employee_id, start_date, end_date, job_
id, department_id)
Dianochka-#     VALUES (OLD.id, v_startdate, CURRENT_DATE, OLD.job_id, OLD.depar
tment_id);
ОШИБКА:  таблица "old" отсутствует в предложении FROM
LINE 2:     VALUES (OLD.id, v_startdate, CURRENT_DATE, OLD.job_id, O...
                    ^
Dianochka=#
Dianochka=#     RETURN NEW;
ОШИБКА:  ошибка синтаксиса (примерное положение: "RETURN")
LINE 1: RETURN NEW;
        ^
Dianochka=# END;
ПРЕДУПРЕЖДЕНИЕ:  нет незавершённой транзакции
COMMIT
Dianochka=# $$ LANGUAGE plpgsql;
Dianochka$#
Dianochka$# CREATE TRIGGER trg_log_job_change
Dianochka$# AFTER UPDATE OF job_id ON employees
Dianochka$# FOR EACH ROW
Dianochka$# EXECUTE FUNCTION trg_log_job_change_func();-- Подготовка тестовых да
нных
Dianochka$# UPDATE employees SET job_id = 'CLERK', hire_date = '2023-01-01', dep
artment_id = 10 WHERE id = 1;
Dianochka$#
Dianochka$# -- Посмотрим текущую историю (пусто)
Dianochka$# SELECT * FROM job_history WHERE employee_id = 1;
Dianochka$#
Dianochka$# -- Меняем должность
Dianochka$# UPDATE employees SET job_id = 'SENIOR_CLERK' WHERE id = 1;
Dianochka$#
Dianochka$# -- Смотрим, что добавилось в историю
Dianochka$# SELECT * FROM job_history WHERE employee_id = 1;
Dianochka$# -- Ожидаемый результат: одна запись с employee_id=1, start_date=2023
-01-01, end_date=сегодня, job_id=CLERK
Dianochka$#
Dianochka$# -- Меняем ещё раз
Dianochka$# UPDATE employees SET job_id = 'MANAGER' WHERE id = 1;
Dianochka$#
Dianochka$# -- Смотрим историю
Dianochka$# SELECT * FROM job_history WHERE employee_id = 1;
Dianochka$# -- Ожидаемый результат: вторая запись с start_date = (предыдущий end
_date + 1)
Dianochka$# commit;
Dianochka$#
