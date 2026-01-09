#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "webdriverxx.h"

using namespace webdriverxx;

const std::string SELENIUM_URL = "http://localhost:4444/wd/hub";

TEST(LoginTests, SuccessfulLogin_G) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    EXPECT_EQ(driver.GetTitle(), "Swag Labs");
    EXPECT_TRUE(driver.FindElement(ByCss(".inventory_list")).IsDisplayed());
}

TEST(LoginTests, InvalidUsername_VG) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("wrong_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    Element error = driver.FindElement(ByCss("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed());
    EXPECT_THAT(error.GetText(), ::testing::HasSubstr("Username and password do not match"));
}

TEST(LoginTests, InvalidPassword_VG) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("wrong_password");
    driver.FindElement(ById("login-button")).Click();

    Element error = driver.FindElement(ByCss("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed());
    EXPECT_THAT(error.GetText(), ::testing::HasSubstr("Username and password do not match"));
}