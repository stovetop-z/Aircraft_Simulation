import os
import subprocess
import sys

def is_built() -> bool:
    return os.path.isdir("build")

def run_pre_built(myapp: str) -> bool:
    executable_path = os.path.join("build", myapp)
    
    result = subprocess.run([f"./{executable_path}"], capture_output=True, text=True)
    
    output = (result.stdout + result.stderr).lower()
    return "failed" in output

def run(myapp: str) -> bool:
    if is_built():
        return run_pre_built(myapp)
    
    os.makedirs("build", exist_ok=True)
    
    subprocess.run(["cmake", ".."], cwd="build", check=True)
    subprocess.run(["cmake", "--build", "."], cwd="build", check=True)
    return True

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py <app_name>")
        sys.exit(1)
        
    run(sys.argv[1])
