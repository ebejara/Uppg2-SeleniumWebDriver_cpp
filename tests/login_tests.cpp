#include <gtest/gtest.h>
#include <webdriverxx.h>  // Huvudheader

using namespace webdriverxx;

const std::string SELENIUM_URL = "http://localhost:4444";

TEST(LoginTests, SuccessfulLogin_G) {
    // Starta Chrome-session
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    // Verifiera inloggning
    EXPECT_EQ(driver.GetTitle(), "Swag Labs");
    EXPECT_TRUE(driver.FindElement(ByCssSelector(".inventory_list")).IsDisplayed());

    driver.Quit();  // Rätt metod för att stänga sessionen
}

TEST(LoginTests, InvalidUsername_VG) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("wrong_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    Element error = driver.FindElement(ByCssSelector("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed());
    EXPECT_THAT(error.GetText(), ::testing::ContainsSubstring("Username and password do not match"));

    driver.Quit();
}

TEST(LoginTests, InvalidPassword_VG) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);

    driver.Navigate("https://www.saucedemo.com/");

    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("wrong_password");
    driver.FindElement(ById("login-button")).Click();

    Element error = driver.FindElement(ByCssSelector("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed());
    EXPECT_THAT(error.GetText(), ::testing::ContainsSubstring("Username and password do not match"));

    driver.Quit();
}