import select
import sys

class TimeoutExpired(Exception):
    pass

def input_with_timeout(prompt, timeout):
    sys.stdout.write(prompt)
    sys.stdout.flush()
    ready, _, _ = select.select([sys.stdin], [],[], timeout)
    
    if ready:
        return sys.stdin.readline().rstrip('\n')
    raise TimeoutExpired