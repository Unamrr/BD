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
