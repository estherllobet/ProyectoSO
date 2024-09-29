CREATE DATABASE battleship_database;
USE battleship_database;

-- Create the users table
CREATE TABLE users (
    id_user INT PRIMARY KEY AUTO_INCREMENT, -- Unique identifier for each user
    username VARCHAR(100) NOT NULL UNIQUE,  -- Ensures username is unique
    password VARCHAR(100) NOT NULL,         -- Use hashed passwords, not plain text
    email VARCHAR(100) NOT NULL UNIQUE,     -- Ensures email is unique
    total_points INT DEFAULT 0              -- Tracks total points earned by the user
);

-- Create the games table
CREATE TABLE games (
    id_game INT PRIMARY KEY AUTO_INCREMENT,  -- Unique identifier for each game
    id_player_1 INT NOT NULL,                -- Reference to player 1 (must exist in users table)
    id_player_2 INT NOT NULL,                -- Reference to player 2 (must exist in users table)
    points_player_1 INT DEFAULT 0,           -- Points scored by player 1
    points_player_2 INT DEFAULT 0,           -- Points scored by player 2
    start_time DATETIME,                     -- Timestamp when the game starts
    end_time DATETIME,                       -- Timestamp when the game ends
    FOREIGN KEY (id_player_1) REFERENCES users(id_user),
    FOREIGN KEY (id_player_2) REFERENCES users(id_user),
    CHECK (id_player_1 != id_player_2)       -- Ensure players are different
);

-- Insert into users table
INSERT INTO users (username, password, email)
VALUES ('manel007', '12345', 'manel.colominas@estudiantat.upc.edu');
