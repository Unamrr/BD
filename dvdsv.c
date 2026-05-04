3
    ALTER TABLE employees ADD COLUMN department_id INTEGER;
UPDATE employees SET department_id = 10 WHERE id = 1;
UPDATE employees SET department_id = 20 WHERE id = 2;
UPDATE employees SET department_id = 10 WHERE id = 3;-- Пытаемся назначить менеджера из другого отдела
-- (сотрудник id=3 в отделе 10, менеджер id=2 в отделе 20)
UPDATE employees SET manager = 2 WHERE id = 3;

5 
    ALTER TABLE employees ADD COLUMN job_id VARCHAR(20);
ALTER TABLE employees ADD COLUMN hire_date DATE;

UPDATE employees SET job_id = 'CLERK', hire_date = '2023-01-01' WHERE id = 1;
UPDATE employees SET job_id = 'MANAGER', hire_date = '2022-06-15' WHERE id = 2;CREATE TABLE IF NOT EXISTS job_history (
    employee_id INTEGER,
    start_date DATE,
    end_date DATE,
    job_id VARCHAR(20),
    department_id INTEGER
);-- Посмотрим текущую историю для сотрудника id=1
SELECT * FROM job_history WHERE employee_id = 1;

-- Меняем должность
UPDATE employees SET job_id = 'SENIOR_CLERK' WHERE id = 1;

-- Смотрим, что добавилось в историю
SELECT * FROM job_history WHERE employee_id = 1;


CREATE OR REPLACE FUNCTION trg_employees_salary_check_func()
RETURNS TRIGGER AS
$$
BEGIN
    IF OLD.salary > NEW.salary THEN
        RAISE EXCEPTION 'Sorry! Salary can not be decreased!';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_employees_salary_check
BEFORE UPDATE ON employees
FOR EACH ROW
EXECUTE FUNCTION trg_employees_salary_check_func();

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

-- Сначала создадим таблицу job_history (если её нет)
CREATE TABLE IF NOT EXISTS job_history (
    employee_id INTEGER,
    start_date DATE,
    end_date DATE,
    job_id VARCHAR(10),
    department_id INTEGER
);

CREATE OR REPLACE FUNCTION trg_log_job_change_func()
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
EXECUTE FUNCTION trg_log_job_change_func();
Dianochka=# \d employees
                                  Table "public.employees"
 Column  |       Type        | Collation | Nullable |                Default

---------+-------------------+-----------+----------+---------------------------
------------
 id      | integer           |           | not null | nextval('employees_id_seq'
::regclass)
 name    | character varying |           |          |
 manager | integer           |           |          |
Indexes:
    "employees_pkey" PRIMARY KEY, btree (id)
Foreign-key constraints:
    "employees_manager_fkey" FOREIGN KEY (manager) REFERENCES employees(id)
Referenced by:
    TABLE "employees" CONSTRAINT "employees_manager_fkey" FOREIGN KEY (manager)
REFERENCES employees(id)
Triggers:
    trg_employees_time_check BEFORE INSERT OR DELETE OR UPDATE ON employees FOR
EACH ROW EXECUTE FUNCTION trg_employees_time_check_func()

