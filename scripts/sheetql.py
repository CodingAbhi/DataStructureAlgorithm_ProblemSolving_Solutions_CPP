import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.common.exceptions import SessionNotCreatedException
from webdriver_manager.chrome import ChromeDriverManager

def setup_chrome_options():
    options = webdriver.ChromeOptions()
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-dev-shm-usage')
    options.add_argument('--disable-gpu')
    options.add_argument(r"--user-data-dir=C:\Users\Asus\AppData\Local\Google\Chrome\User Data")
    options.add_argument(r"--profile-directory=Profile 1")
    options.add_argument('--remote-debugging-port=9222')
    options.add_experimental_option("excludeSwitches", ["enable-automation"])
    options.add_experimental_option('useAutomationExtension', False)
    return options
def process_linkedin_data(csv_file_path):
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))
    try:
        data = pd.read_csv(csv_file_path)
        
        service = Service(ChromeDriverManager().install())
        options = setup_chrome_options()
        driver = webdriver.Chrome(service=service, options=options)
        
        for index, row in data.iterrows():
            linkedin_url = row['Linkedin url']
            company_name = row['COMPANY']
            email = row.get('Email', None)

            if pd.notna(email) or pd.isna(linkedin_url):
                print(f"Skipping row {index}: Email exists or LinkedIn URL missing")
                continue
                
            driver.get(linkedin_url)
            
    except SessionNotCreatedException as e:
         print(f"Chrome version mismatch: {str(e)}")
         print("Please update Chrome browser or ChromeDriver")
    except Exception as e:
        print(f"Browser initialization failed: {str(e)}")
    finally:
        if driver:
            try:
                driver.quit()
            except Exception as e:
                print(f"Error while closing browser: {str(e)}")

if __name__ == "__main__":
    csv_file_path = r"C:\Users\Asus\Downloads\AD_internsheet_1-Sheet2.csv"
    process_linkedin_data(csv_file_path)
