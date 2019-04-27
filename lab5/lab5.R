results = read.csv("dane.csv", sep = ";", dec =".")
results

avg_results = aggregate( time ~size:type, data=results, FUN=mean )
avg_results$sd = aggregate( time ~ size:type, data=results, FUN=sd)$time

avg_results

x1 = avg_results$size[avg_results$type==1]
y1 = avg_results$time[avg_results$type==1]
x2 = avg_results$size[avg_results$type==2]
y2 = avg_results$time[avg_results$type==2]

avg_results1 = data.frame(x1,y1)
avg_results2 = data.frame(x2,y2)
avg_results1$sd = avg_results$sd[avg_results$type==1]
avg_results1


fit1 = lm(y1 ~ poly(x1, 3, raw=TRUE), data=avg_results1)
fit2 = lm(y2 ~ poly(x2, 3, raw=TRUE), data=avg_results2)

newdata1 = data.frame(x = seq(1000,10000, length.out=10))
newdata1$y = predict(fit1, newdata1)
newdata1$type = 1
newdata2 = data.frame(x = seq(1000,10000, length.out=10))
newdata2$y = predict(fit2, newdata2)
newdata2$type = 2


ggplot(avg_results, aes(size,time, color=type)) +
  geom_errorbar(aes(ymin=time-sd, ymax=time+sd), width=.1) +
  geom_point() + geom_line(data=newdata1, aes(x,y)) +
  geom_line(data=newdata2, aes(x,y))

#ggplot(avg_results1, aes(x1,y1)) +
#  geom_errorbar(aes(ymin=y1-sd, ymax=y1+sd), width=.1) +
#  geom_point() + geom_line(data=newdata1, aes(x,y))