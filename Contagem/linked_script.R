linkedcomparisons <- linkedcomparisons[order(linkedcomparisons$comparações),]
linkedcomparisons["Casos"] <- NA
linkedcomparisons$Casos <- c(1:1000)
graph <- ggplot(linkedcomparisons, aes(linkedcomparisons$Casos)) + geom_smooth(aes(,linkedcomparisons$comparações), span = 0.2, color = "black") + labs(list(title = "Linked List", x = "", y = "Comparisons")) + theme(plot.title = element_text(lineheight=.8, face="bold"))

