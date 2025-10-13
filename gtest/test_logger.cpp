/**
 * @file test_logger.cpp
 * @brief Unit tests for the Logger class.
 *
 * This file contains tests for the Logger class, verifying its
 * functionality, including log level management, output streams,
 * and message formatting.
 *
 * @author Oliver Merkel
 * @date 2025-10-13
 */
#include "gtest/gtest.h"
#include "Logger.h"
#include <fstream>
#include <string>
#include <sstream>

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure log file is clean before each test
        std::ofstream ofs(testLogFile, std::ios::trunc);
        ofs.close();
        Logger::instance().setLogFile(""); // Disable file
        Logger::instance().enableConsole(false); // Disable console for tests
        Logger::instance().setAllLevels(Logger::Level::Trace);
    }
    void TearDown() override {
        Logger::instance().setLogFile(""); // Clean up
    }
    const std::string testLogFile = "logger_test.log";
};

TEST_F(LoggerTest, ConsoleEnableDisable) {
    Logger& logger = Logger::instance();
    logger.enableConsole(true);
    EXPECT_TRUE(logger.consoleLevel() <= Logger::Level::Critical);
    logger.enableConsole(false);
    EXPECT_TRUE(logger.consoleLevel() <= Logger::Level::Critical);
}

TEST_F(LoggerTest, FileEnableDisable) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    EXPECT_TRUE(logger.fileLevel() <= Logger::Level::Critical);
    logger.enableFile(false);
    EXPECT_TRUE(logger.fileLevel() <= Logger::Level::Critical);
}

TEST_F(LoggerTest, SetAllLevels) {
    Logger& logger = Logger::instance();
    logger.setAllLevels(Logger::Level::Warn);
    EXPECT_EQ(logger.consoleLevel(), Logger::Level::Warn);
    EXPECT_EQ(logger.fileLevel(), Logger::Level::Warn);
}

TEST_F(LoggerTest, LogStreamEmit) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);
    {
        auto log = logger.info();
        log << "Info message" << std::endl;
    }
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Info message"), std::string::npos);
}

TEST_F(LoggerTest, LogStreamMoveSemantics) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);
    {
        auto log1 = logger.debug();
        log1 << "Debug message";
        auto log2 = std::move(log1);
        log2 << " moved" << std::endl;
    }
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Debug message moved"), std::string::npos);
}

TEST_F(LoggerTest, LogStreamFlush) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);
    auto log = logger.warn();
    log << "Warn message";
    log.flush();
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Warn message"), std::string::npos);
}

TEST_F(LoggerTest, LogLevels) {
    Logger& logger = Logger::instance();
    logger.setConsoleLevel(Logger::Level::Error);
    logger.setFileLevel(Logger::Level::Error);
    EXPECT_EQ(logger.consoleLevel(), Logger::Level::Error);
    EXPECT_EQ(logger.fileLevel(), Logger::Level::Error);
}

TEST_F(LoggerTest, LogStreamManipulators) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);
    {
        auto log = logger.critical();
        log << "Critical message" << std::endl;
    }
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Critical message"), std::string::npos);
}

TEST_F(LoggerTest, TraceLevelLogging) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);
    {
        auto log = logger.trace();
        log << "Trace level message" << std::endl;
    }
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Trace level message"), std::string::npos);
    EXPECT_NE(line.find("TRACE"), std::string::npos); // Assuming log format includes level
}

TEST_F(LoggerTest, OffLevelLogging) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Off);
    {
        auto log = logger.log(Logger::Level::Off);
        log << "Off level message" << std::endl;
    }
    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    EXPECT_NE(line.find("Off level message"), std::string::npos);
    EXPECT_NE(line.find("OFF"), std::string::npos); // Assuming log format includes level
}

TEST_F(LoggerTest, SetInvalidFileName) {
    Logger& logger = Logger::instance();
    // Attempt to set an invalid file name being an empty string
    std::string invalidFileName = std::string("", 13);
    bool result = logger.setLogFile(invalidFileName, false);
    EXPECT_FALSE(result);
}

TEST_F(LoggerTest, LoggingDisabled_NoConsoleNoFile) {
    Logger& logger = Logger::instance();
    logger.enableConsole(false);
    logger.enableFile(false);
    logger.setConsoleLevel(Logger::Level::Critical); // Set high level
    logger.setFileLevel(Logger::Level::Critical);    // Set high level
    // No log file set, fileEnabled_ is false
    // This should not log to console or file    
    // Redirect std::cout to a stringstream to capture output
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    {
        auto log = logger.info();
        log << "This should not appear anywhere" << std::endl;
        log << "Console should not see this" << std::endl;
    }

    std::cout.rdbuf(oldCout); // Restore original buffer

    // Since console is disabled, buffer should be empty
    EXPECT_EQ(buffer.str(), "");
}

TEST_F(LoggerTest, NoConsoleOutputWhenDisabled) {
    Logger& logger = Logger::instance();
    logger.enableConsole(false);
    logger.setConsoleLevel(Logger::Level::Trace);

    // Redirect std::cout to a stringstream to capture output
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    {
        auto log = logger.info();
        log << "Console should not see this" << std::endl;
    }

    std::cout.rdbuf(oldCout); // Restore original buffer

    // Since console is disabled, buffer should be empty
    EXPECT_EQ(buffer.str(), "");
}

TEST_F(LoggerTest, ConsoleOutputWhenEnabled) {
    Logger& logger = Logger::instance();
    logger.enableConsole(true);
    logger.setConsoleLevel(Logger::Level::Trace);

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    {
        auto log = logger.info();
        log << "Console should see this" << std::endl;
    }

    std::cout.rdbuf(oldCout);

    // Should contain the message
    EXPECT_NE(buffer.str().find("Console should see this"), std::string::npos);
}

TEST_F(LoggerTest, FileOutputDisabled_NoFileWritten) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(false);
    logger.setFileLevel(Logger::Level::Trace);

    {
        auto log = logger.info();
        log << "File should not see this" << std::endl;
    }

    std::ifstream ifs(testLogFile);
    std::string line;
    std::getline(ifs, line);
    // File should be empty
    EXPECT_EQ(line, "");
}

TEST_F(LoggerTest, MultipleLogLevelsInOneFile) {
    Logger& logger = Logger::instance();
    logger.setLogFile(testLogFile, false);
    logger.enableFile(true);
    logger.setFileLevel(Logger::Level::Trace);

    {
        auto log1 = logger.trace();
        log1 << "Trace message" << std::endl;
        auto log2 = logger.debug();
        log2 << "Debug message" << std::endl;
        auto log3 = logger.info();
        log3 << "Info message" << std::endl;
        auto log4 = logger.warn();
        log4 << "Warn message" << std::endl;
        auto log5 = logger.error();
        log5 << "Error message" << std::endl;
        auto log6 = logger.critical();
        log6 << "Critical message" << std::endl;
    }

    std::ifstream ifs(testLogFile);
    std::string contents((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    EXPECT_NE(contents.find("Trace message"), std::string::npos);
    EXPECT_NE(contents.find("Debug message"), std::string::npos);
    EXPECT_NE(contents.find("Info message"), std::string::npos);
    EXPECT_NE(contents.find("Warn message"), std::string::npos);
    EXPECT_NE(contents.find("Error message"), std::string::npos);
    EXPECT_NE(contents.find("Critical message"), std::string::npos);
}
