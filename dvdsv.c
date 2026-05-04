3
CREATE OR REPLACE FUNCTION trg_employee_manager_same_dept_func()
RETURNS TRIGGER AS
$$
DECLARE
    manager_dept_id INTEGER;
BEGIN
    SELECT department_id INTO manager_dept_id
    FROM employees
    WHERE id = NEW.manager;
    
    IF manager_dept_id != NEW.department_id THEN
        RAISE EXCEPTION 'Employee and manager must belong to the same department';
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_employee_manager_same_dept
BEFORE INSERT OR UPDATE OF department_id, manager ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_employee_manager_same_dept_func();
-- Подготовка тестовых данных
UPDATE employees SET department_id = 10, manager = NULL WHERE id = 1;
UPDATE employees SET department_id = 20, manager = 1 WHERE id = 2;
UPDATE employees SET department_id = 10, manager = 1 WHERE id = 3;

-- НЕЛЬЗЯ — менеджер из другого отдела (сотрудник id=3 в отделе 10, менеджер id=2 в отделе 20)
UPDATE employees SET manager = 2 WHERE id = 3;
-- Ожидаемая ошибка: ERROR: Employee and manager must belong to the same department

-- МОЖНО — менеджер из того же отдела (id=1 в отделе 10)
UPDATE employees SET manager = 1 WHERE id = 3;
-- Ожидаемый результат: успешно


  4 
  CREATE TABLE IF NOT EXISTS job_history (
    employee_id INTEGER,
    start_date DATE,
    end_date DATE,
    job_id VARCHAR(20),
    department_id INTEGER
);CREATE OR REPLACE FUNCTION trg_log_job_change_func()
RETURNS TRIGGER AS
$$
DECLARE
    v_enddate DATE;
    v_startdate DATE;
BEGIN
    SELECT MAX(end_date) INTO v_enddate
    FROM job_history
    WHERE employee_id = OLD.id;
    
    IF v_enddate IS NULL THEN
        v_startdate := OLD.hire_date;
    ELSE
        v_startdate := v_enddate + 1;
    END IF;
    
    INSERT INTO job_history (employee_id, start_date, end_date, job_id, department_id)
    VALUES (OLD.id, v_startdate, CURRENT_DATE, OLD.job_id, OLD.department_id);
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_job_change
AFTER UPDATE OF job_id ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_log_job_change_func();-- Подготовка тестовых данных
UPDATE employees SET job_id = 'CLERK', hire_date = '2023-01-01', department_id = 10 WHERE id = 1;

-- Посмотрим текущую историю (пусто)
SELECT * FROM job_history WHERE employee_id = 1;

-- Меняем должность
UPDATE employees SET job_id = 'SENIOR_CLERK' WHERE id = 1;

-- Смотрим, что добавилось в историю
SELECT * FROM job_history WHERE employee_id = 1;
-- Ожидаемый результат: одна запись с employee_id=1, start_date=2023-01-01, end_date=сегодня, job_id=CLERK

-- Меняем ещё раз
UPDATE employees SET job_id = 'MANAGER' WHERE id = 1;

-- Смотрим историю
SELECT * FROM job_history WHERE employee_id = 1;
-- Ожидаемый результат: вторая запись с start_date = (предыдущий end_date + 1)
