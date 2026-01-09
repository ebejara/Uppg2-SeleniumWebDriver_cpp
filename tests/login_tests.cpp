#include <gtest/gtest.h>
#include <selenium/webdriver.h>  // main include - check exact path after cloning

using namespace selenium;

const std::string SELENIUM_URL = "http://localhost:4444";

TEST(LoginTests, SuccessfulLogin_G) {
    WebDriver driver = WebDriver(SELENIUM_URL, Capabilities::Chrome());

    driver.Get("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    EXPECT_EQ(driver.Title(), "Swag Labs");
    EXPECT_TRUE(driver.FindElement(ByCss(".inventory_list")).IsDisplayed());

    driver.Quit();
}

// Repeat similar pattern for InvalidUsername_VG and InvalidPassword_VG