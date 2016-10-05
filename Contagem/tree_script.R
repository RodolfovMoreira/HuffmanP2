treecomparisons<-treecomparisons[order(treecomparisons$Comparar),]
treecomparisons["Casos"] <- NA
treecomparisons$Casos <- c(1:1000)
graph <- ggplot(treecomparisons, aes(treecomparisons$Casos, treecomparisons$Comparacoes)) + geom_smooth(span = 0.2, color = "black") + labs(list(title = "Binary Search Tree", x = "", y = "Comparisons")) + theme(plot.title = element_text(lineheight=.8, face="bold"))

