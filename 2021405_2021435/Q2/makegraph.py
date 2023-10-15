import matplotlib.pyplot as plto

dfifo=[]
with open('FIFO.txt','r') as file:
    info=file.readlines()
    dfifo=[float(i.strip()) for i in info]

dother=[]
with open('OTHER.txt','r') as file:
    info=file.readlines()
    dother=[float(i.strip()) for i in info]

drr =[]
with open('RR.txt', 'r') as file:
    info=file.readlines()
    drr=[float(i.strip()) for i in info]

avgfifo=sum(dfifo)/len(dfifo)
avgother=sum(dother)/len(dother)
avgrr=sum(drr)/len(drr)

plto.bar(['FIFO', 'OTHER', 'RR'],[avgfifo, avgother, avgrr])
plto.xlabel('Scheduling Policy')
plto.ylabel('Time')
plto.title('Average Time of scheduling policies')
plto.savefig("histogram.png")

