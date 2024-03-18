DECLARE @dbName NVARCHAR(128) = N'PhoneBook';
DECLARE @sql NVARCHAR(MAX);

IF NOT EXISTS (SELECT * FROM sys.databases WHERE name = @dbName)
BEGIN
    SET @sql = N'CREATE DATABASE ' + QUOTENAME(@dbName) + N'
    ON PRIMARY
        (NAME = sample_database_file1,
        FILENAME = N''C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\Data\Datasample_database_1.mdf'',
        SIZE = 10MB,
        MAXSIZE = 50MB,
        FILEGROWTH = 10%)
    LOG ON
        (NAME = sample_database_log_file1,
        FILENAME = N''C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\Data\Datasample_database_1.ldf'',
        SIZE = 10MB,
        MAXSIZE = 50MB,
        FILEGROWTH = 10%)';

    EXEC sp_executesql @sql;
    PRINT 'Database created!';
END
ELSE
BEGIN
    PRINT 'Database exists! Doing nothing.';
END
