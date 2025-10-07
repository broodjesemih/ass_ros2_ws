-- Initialize database for Cijfer Generator
-- This script runs automatically when the PostgreSQL container starts

-- Create the main table
CREATE TABLE IF NOT EXISTS student_results (
    id SERIAL PRIMARY KEY,
    student_name VARCHAR(255) NOT NULL,
    course VARCHAR(255) NOT NULL,
    number_of_exams INTEGER DEFAULT 0,
    final_result REAL DEFAULT 0,
    timestamp BIGINT DEFAULT EXTRACT(EPOCH FROM NOW())
);

-- Clear existing data and insert new student/course combinations
DELETE FROM student_results;

-- Insert new student/course combinations
INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES
('Semih', 'Calculus', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Vincent', 'ROS2', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Wessel', 'Natuurkunde', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Tilmann', 'Economie', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Tycho', 'Calculus', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Nout', 'ROS2', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Burhan', 'Natuurkunde', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Jan', 'Economie', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Semih', 'ROS2', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Vincent', 'Natuurkunde', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Wessel', 'Calculus', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Tilmann', 'ROS2', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Tycho', 'Economie', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Nout', 'Natuurkunde', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Burhan', 'Calculus', 0, 0, EXTRACT(EPOCH FROM NOW())),
('Jan', 'ROS2', 0, 0, EXTRACT(EPOCH FROM NOW()));

-- Create indexes for better performance
CREATE INDEX IF NOT EXISTS idx_student_course ON student_results(student_name, course);
CREATE INDEX IF NOT EXISTS idx_final_result ON student_results(final_result);
CREATE INDEX IF NOT EXISTS idx_timestamp ON student_results(timestamp);

-- Show initial data
SELECT 'Initial data inserted:' as message;
SELECT student_name, course FROM student_results ORDER BY student_name;
