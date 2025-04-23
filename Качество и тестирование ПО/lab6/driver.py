import importlib.util
import json
import os
from pathlib import Path


class TestDriver:
    def __init__(self, module_path, test_file):
        self.module_path = module_path
        self.test_file = test_file

    def load_module(self, module_name):
        spec = importlib.util.spec_from_file_location(module_name, self.module_path / f"{module_name}.py")
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module

    def run_tests(self):
        with open(self.test_file, 'r') as file:
            tests = json.load(file)
        
        results = []
        for i, test in enumerate(tests, start=1):
            try:
                module = self.load_module(test['module'])
                func = getattr(module, test['name'], None)
                if not callable(func):
                    raise AttributeError(f"Function {test['name']} is not found or not callable.")
                
                result = func(*test['params'])
                expected_result = test['expected_result']
                status = 'success' if result == expected_result else 'faile'
                message = '' if status == 'success' else f"Expected {expected_result}, got {result}"

                results.append({
                    'test_number': i,
                    'received_result': result,
                    'expected_result': expected_result,
                    'status': status,
                    'message': message
                })
            
            except Exception as e:
                results.append({
                    'test_number': i,
                    'received_result': '',
                    'expected_result': test.get('expected_result', ''),
                    'status': 'faile',
                    'message': str(e)
                })
        
        return results

    def generate_report(self, results):
        if os.name == 'nt':  # Windows
            os.system('color')  # Включаем поддержку ANSI цветов в Windows 10+
    
        RED = '\033[31m'
        GREEN = '\033[32m'
        RESET = '\033[0m'

        for result in results:
            report = "\n"
            report += f"\nTest #{result['test_number']}: {f'{GREEN}Success{RESET}' if result['status'] == 'success' else f'{RED}Failed{RESET}'}" 
            report += f"\n\tReceived Result: {result['received_result']}" 
            report += f"\n\tExpected Result: {result['expected_result']}"  
            report += f"\n\tMessage: {result['message']}" if result['message'] else ""
            print(report)


if __name__ == "__main__":
    module_path = Path("test_modules")  # Путь к папке с тестируемыми модулями
    test_file = "tests.json"  # Файл с тестами

    driver = TestDriver(module_path, test_file)
    results = driver.run_tests()
    driver.generate_report(results)