import cv2
import time
import os
import HandTrackingModule as htm

class FingerCounter():
    def __init__(self):
        self.folderPath = "FingerImages"
        self.myList = os.listdir(self.folderPath)
        self.myList = sorted(self.myList)
        # print(self.myList)
        self.overlayList = []
        for imPath in self.myList:
            image = cv2.imread(f'{self.folderPath}/{imPath}')
            self.overlayList.append(image)
        self.pTime = 0
        self.detector = htm.handDetector(detectionCon=0.75)
        self.tipIds = [4, 8, 12, 16, 20]

    def recognizeFinger(self, img):
        img = self.detector.findHands(img)
        lmList = self.detector.findPosition(img, draw=False)

        if len(lmList) != 0:
            fingers = []

            # Thumb
            if lmList[self.tipIds[0]][1] > lmList[self.tipIds[0] - 1][1]:
                fingers.append(1)
            else:
                fingers.append(0)

            # 4 Fingers
            for id in range(1, 5):
                if lmList[self.tipIds[id]][2] < lmList[self.tipIds[id] - 2][2]:
                    fingers.append(1)
                else:
                    fingers.append(0)


            totalFingers = fingers.count(1)
            h, w, c = self.overlayList[totalFingers - 1].shape
            img[0:h, 0:w] = self.overlayList[totalFingers - 1]
            
            
            cv2.putText(img, str(totalFingers), (45, 375), cv2.FONT_HERSHEY_PLAIN, 10, (255, 0, 0), 25)
            cv2.imshow("Image", img)
            cv2.waitKey(150)
           
            
            if(totalFingers):
                # print(totalFingers)
                return totalFingers  
            else:
                # print(totalFingers)
                return 0




