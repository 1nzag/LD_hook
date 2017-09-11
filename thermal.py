import glob
from time import *
from subprocess import *
import random
import os
from time import *

format_string = ["%s","%n"]



def pseudo_radamsa(seedlist,path,dir,store):
    sample = ""
    print "go to grease"
    for seed in seedlist:
        if "bof" in seed:
            sample += "A" * random.randrange(0x100,0x3000)
        elif "format_string" in seed:
            formatchar = format_string[random.randrange(0,2)]
            for i in range(random.randrange(0,10)):
                sample += formatchar * random.randrange(0,0x10)
                if random.randrange(0,1000) % 2 == 0 :
                    sample += ("%" + str(random.randrange(1,0x100))+ formatchar[1])
        if not (dir in glob.glob(path)):
            try:
                os.mkdir(path + "/" +store)
            except:
                print "exist"
        fuzz = glob.glob("crashes/test/sync/*")
        #print fuzz
        grease_list = []
        for job in fuzz:
            if "fuzzer" in job:
                print glob.glob(job + "/.cur_input")
                if (job + "/.cur_input") in glob.glob(job + "/.cur_input"):
                    os.system("cp " + job + "/.cur_input res/cur_input_back;chmod 777 res/cur_input_back")
                    sleep(0.5)
                    f = open("res/cur_input_back","rb")
                    grease_list.append(f.read())
                    f.close()
        for i in range(len(grease_list)):
            seedname = seed.split("./thermal_grease/seeds/")[1]
            seedname = seedname.split("/")[1] + str(i)
            f = open(path + "/" + store + '/' + seedname, "wb")
            sample = grease_list[i] + sample
            print sample
            f.write(sample)
            f.close()


def explore_seed(path):
     
    while 1:
        sleep(1)
        dirlist = glob.glob("./thermal_grease/seeds/*")
        #print dirlist

        for dir in dirlist:
            seed_dir =dir + "/*"
            seedlist = glob.glob(seed_dir)
            store = dir.split("./thermal_grease/seeds/")[1]
            if len(seedlist) > 0  :
                
                pseudo_radamsa(seedlist, path, seed_dir, store)

            



if __name__ == '__main__':
    explore_seed("./thermal_grease/with")
