#include <gtest/gtest.h>
#include <webdriverxx.h>
#include <webdriverxx/browsers/chrome.h>
#include <webdriverxx/by.h>
#include <webdriverxx/wait.h>

using namespace webdriverxx;
using webdriverxx::detail::Wait;
using namespace std::chrono_literals;

const std::string SELENIUM_URL = "http://localhost:4444";


/*class LoginTests : public ::testing::Test {
protected:
    WebDriver driver;

    void SetUp() override {
        // Start Chrome session pointing to Selenium 4
        driver = Start(Chrome(), Capabilities().SetBrowserName("chrome"), SELENIUM_URL);   
        driver.Navigate("https://www.saucedemo.com/");
    }

    void TearDown() override {
        // WebDriverXX closes browser automatically
    }
};*/

TEST(LoginTests, SuccessfulLogin) {
    
      WebDriver driver = Start(Chrome(), SELENIUM_URL);
    driver.Navigate("https://www.saucedemo.com/");
    
    auto username = driver.FindElement(ByName("user-name"));
    auto password = driver.FindElement(ByName("password"));
    auto loginBtn = driver.FindElement(ById("login-button"));

    driver.FindElement(ById("user-name"))
      .SendKeys("standard_user");

    driver.FindElement(ById("password"))
      .SendKeys("secret_sauce");

    driver.FindElement(ById("login-button"))
      .Click();

   bool pageLoaded = false;

    Wait<bool>([&](std::string*) -> bool* {
        pageLoaded = !driver.FindElements(ByCss(".title")).empty();
        return pageLoaded ? &pageLoaded : nullptr;
}, 5000);

    auto title = driver.FindElement(ByCss(".title"));
    EXPECT_EQ(title.GetText(), "PRODUCTS");
}

TEST(LoginTests, InvalidUsername) {
     WebDriver driver = Start(Chrome(), SELENIUM_URL);
    driver.Navigate("https://www.saucedemo.com/");
    
    auto username = driver.FindElement(ByName("username"));
    auto password = driver.FindElement(ByName("password"));
    auto loginBtn = driver.FindElement(ByCss("button[type='submit']"));

    username.SendKeys("wrong_user");
    password.SendKeys("secret_password");
    loginBtn.Click();

    auto errorMsg = driver.FindElement(ByCss("#error-message"));
    std::string text = errorMsg.GetText();
    EXPECT_EQ(text, "Invalid username or password.");
}

TEST(LoginTests, InvalidPassword) {
    WebDriver driver = Start(Chrome(), SELENIUM_URL);
    driver.Navigate("https://www.saucedemo.com/");
    
    auto username = driver.FindElement(ByName("username"));
    auto password = driver.FindElement(ByName("password"));
    auto loginBtn = driver.FindElement(ByCss("button[type='submit']"));

    username.SendKeys("standard_user");
    password.SendKeys("wrong_password");
    loginBtn.Click();

    auto errorMsg = driver.FindElement(ByCss("#error-message"));
    std::string text = errorMsg.GetText();
    EXPECT_EQ(text, "Invalid username or password.");
}
