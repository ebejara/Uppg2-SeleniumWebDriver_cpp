#include <gtest/gtest.h>
#include <webdriverxx.h>  // Från webdriverxx

using namespace webdriverxx;

// Selenium Server URL (starta med java -jar selenium-server.jar standalone)
const std::string SELENIUM_URL = "http://localhost:4444/wd/hub";

TEST(LoginTests, SuccessfulLogin_G) {
    // Starta Chrome-session via Selenium
    Capabilities caps;
    caps.SetBrowserName("chrome");
    WebDriver driver(SELENIUM_URL, caps);

    // Gå till saucedemo.com
    driver.Navigate("https://www.saucedemo.com/");

    // Ange korrekt username och password
    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    // Verifiera att vi är på startsidan (t.ex. via title eller element)
    EXPECT_EQ(driver.GetTitle(), "Swag Labs") << "Borde landa på startsidan efter lyckad login";
    EXPECT_TRUE(driver.FindElement(ByCssSelector(".inventory_list")).IsDisplayed()) 
        << "Inventarielistan ska visas efter login";

    driver.Quit();
}

TEST(LoginTests, InvalidUsername_VG) {
    Capabilities caps;
    caps.SetBrowserName("chrome");
    WebDriver driver(SELENIUM_URL, caps);

    driver.Navigate("https://www.saucedemo.com/");

    // Fel username, korrekt password
    driver.FindElement(ById("user-name")).SendKeys("invalid_user");
    driver.FindElement(ById("password")).SendKeys("secret_sauce");
    driver.FindElement(ById("login-button")).Click();

    // Verifiera felmeddelande
    Element error = driver.FindElement(ByCssSelector("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed()) << "Felmeddelande ska visas vid fel username";
    EXPECT_EQ(error.GetText(), "Epic sadface: Username and password do not match any user in this service") 
        << "Felaktigt felmeddelande vid fel username";

    driver.Quit();
}

TEST(LoginTests, InvalidPassword_VG) {
    Capabilities caps;
    caps.SetBrowserName("chrome");
    WebDriver driver(SELENIUM_URL, caps);

    driver.Navigate("https://www.saucedemo.com/");

    // Korrekt username, fel password
    driver.FindElement(ById("user-name")).SendKeys("standard_user");
    driver.FindElement(ById("password")).SendKeys("invalid_password");
    driver.FindElement(ById("login-button")).Click();

    // Verifiera felmeddelande
    Element error = driver.FindElement(ByCssSelector("[data-test='error']"));
    EXPECT_TRUE(error.IsDisplayed()) << "Felmeddelande ska visas vid fel password";
    EXPECT_EQ(error.GetText(), "Epic sadface: Username and password do not match any user in this service") 
        << "Felaktigt felmeddelande vid fel password";

    driver.Quit();
}