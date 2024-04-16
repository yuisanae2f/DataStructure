import os
import settings as s

def files(r, _ext):
    rtn = []

    for root, _, files in os.walk(r):
        for file in files:
            if _ext == 'o':
                if file.endswith('.o'):
                    print("found: " + os.path.join(root, file))
                    rtn.append(os.path.join(root, file))
            else:
                path, ext = os.path.splitext(os.path.join(root, file))
                if ext in s.ext[_ext]:
                    print("found: " + path + ext)
                    rtn.append(path + ext)
                    pass

    return rtn

if __name__ == "__main__":
    llen = 0
    for cc in ['c', 'cpp']:
        for i in files(s.path['sources'], cc):
            cmd = s.path[cc] + ' -c ' + i + ' -o ' + s.path['obj'] + '/' + i.replace('/', '').replace('.', '').replace('\\','') + str(llen) + '.o'
            llen += 1
            print("Compile: " + cmd)
            os.system(cmd)

    cmd = s.path['cpp'] + ' -o ' + s.path['build'] + ' ' + ''.join((e + ' ') for e in files(s.path['obj'], 'o'))
    cmd = cmd if s.super_ignore_and_just_run_this == '' else s.super_ignore_and_just_run_this
    print("Run: " + cmd)
    os.system(cmd)