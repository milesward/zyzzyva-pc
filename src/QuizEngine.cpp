//---------------------------------------------------------------------------
// QuizEngine.cpp
//
// The engine for generating quizzes and keeping track of the user's
// performance on each quiz.
//
// Copyright 2004 Michael W Thelen.  Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears in
// all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//---------------------------------------------------------------------------

#include "QuizEngine.h"
#include "WordEngine.h"
#include <cstdlib>
#include <ctime>

QuizEngine::QuizEngine (WordEngine* e)
    : wordEngine (e)
{
    std::time_t now = std::time (0);
    std::srand (now);
}

//---------------------------------------------------------------------------
// newQuiz
//
//! Begin a new quiz.
//
//! @param input the group of symbols forming the basis of the quiz
//---------------------------------------------------------------------------
void
QuizEngine::newQuiz (const QString& input, MatchType type, bool alphagrams,
                     bool randomOrder)
{
    quizQuestions.clear();

    quizType = type;

    if (alphagrams) {
        switch (type) {
            case Pattern:
            quizQuestions = wordEngine->matchPattern (input);
            // If using Pattern match with alphagram, change quiz type
            // to Anagram.  The pattern is used to select the list of
            // alphagrams, then anagrams are used as quiz answers.
            quizType = Anagram;
            break;

            case Anagram:
            quizQuestions = wordEngine->matchAnagram (input);
            break;

            case Subanagram:
            quizQuestions = wordEngine->matchSubanagram (input);
            break;

            default: break;
        }

        quizQuestions = wordEngine->alphagrams (quizQuestions);
    }

    else
        quizQuestions << input;

    // Do a random shuffle
    if (randomOrder) {
        QString tmp;
        int num = quizQuestions.size();
        for (int i = 0; i < num ; ++i) {
            int rnum = std::rand() % num;
            if (rnum == i)
                continue;
            tmp = quizQuestions[rnum];
            quizQuestions[rnum] = quizQuestions[i];
            quizQuestions[i] = tmp;
        }
    }

    questionIndex = 0;
    quizTotal = 0;
    quizCorrect = 0;
    quizIncorrect = 0;
    prepareQuestion();
}

//---------------------------------------------------------------------------
// nextQuestion
//
//! Go to the next question in the quiz.
//
//! @return true if there are more questions, false if there are no more
//---------------------------------------------------------------------------
bool
QuizEngine::nextQuestion()
{
    if (onLastQuestion())
        return false;

    ++questionIndex;
    prepareQuestion();
}

//---------------------------------------------------------------------------
// respond
//
//! Enter a user response to the current quiz.
//
//! @param response the user response
//! @return the status of the response
//---------------------------------------------------------------------------
QuizEngine::ResponseStatus
QuizEngine::respond (const QString& response)
{
    if (correctResponses.find (response) == correctResponses.end()) {
        incorrectUserResponses << response;
        ++quizIncorrect;
        return Incorrect;
    }

    if (correctUserResponses.find (response) != correctUserResponses.end())
        return Duplicate;

    correctUserResponses.insert (response);
    ++quizCorrect;
    return Correct;
}

//---------------------------------------------------------------------------
// getQuestion
//
//! Get the question string for the current question.
//
//! @return the current question string
//---------------------------------------------------------------------------
QString
QuizEngine::getQuestion() const
{
    QStringList::const_iterator it = quizQuestions.at (questionIndex);
    return it == quizQuestions.end() ? QString::null : *it;
}

//---------------------------------------------------------------------------
// getMissed
//
//! Get a list of correct responses that have not been answered yet.
//
//! @return the unanswered responses
//---------------------------------------------------------------------------
QStringList
QuizEngine::getMissed() const
{
    QStringList responses;
    std::set<QString>::iterator it;
    for (it = correctResponses.begin(); it != correctResponses.end(); ++it)
        if (correctUserResponses.find (*it) == correctUserResponses.end())
            responses << *it;

    return responses;
}

//---------------------------------------------------------------------------
// onLastQuestion
//
//! Determine whether the current quiz is on the last question.
//
//! @return true if on the last question, false otherwise
//---------------------------------------------------------------------------
bool
QuizEngine::onLastQuestion() const
{
    return (questionIndex == quizQuestions.size() - 1);
}

//---------------------------------------------------------------------------
// clearQuestion
//
//! Clear all answers and user responses.
//---------------------------------------------------------------------------
void
QuizEngine::clearQuestion()
{
    correctResponses.clear();
    correctUserResponses.clear();
    incorrectUserResponses.clear();
}

//---------------------------------------------------------------------------
// prepareQuestion
//
//! Get the answers to the current question.
//---------------------------------------------------------------------------
void
QuizEngine::prepareQuestion()
{
    clearQuestion();
    QString question = getQuestion();

    QStringList answers;
    switch (quizType) {
        case Pattern:
        answers = wordEngine->matchPattern (question);
        break;

        case Anagram:
        answers = wordEngine->matchAnagram (question);
        break;

        case Subanagram:
        answers = wordEngine->matchSubanagram (question);
        break;

        default: break;
    }

    QStringList::iterator it;
    for (it = answers.begin(); it != answers.end(); ++it) {
        correctResponses.insert (*it);
    }
    quizTotal += correctResponses.size();
}
